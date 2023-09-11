#include "avdl_engine.h"
#include <avdl_assetManager.h>
#include <dd_string3d.h>

#ifdef AVDL_DIRECT3D11
#include "pch.h"
using namespace concurrency;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::UI::Popups;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;

using namespace Microsoft::WRL;
using namespace Platform;
using namespace DirectX;

struct VertexPositionColor
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 color;
};

struct ModelViewProjectionConstantBuffer
{
	DirectX::XMFLOAT4X4 model;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};
/*
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <assert.h>
#include <dd_log.h>
#include "dd_game.h"
#include "avdl_assetManager.h"
#include "avdl_steam.h"
#include <wchar.h>

#include <Windows.h>
*/
// temp cube
extern ComPtr<ID3D11Buffer> avdl_constantBuffer;
extern ModelViewProjectionConstantBuffer avdl_constantBufferData;
extern ComPtr<ID3D11VertexShader> avdl_vertexShader;
extern ComPtr<ID3D11PixelShader> avdl_pixelShader;
extern ComPtr<ID3D11InputLayout> avdl_inputLayout;
extern ComPtr<ID3D11Buffer> avdl_vertexBuffer;

#ifdef __cplusplus
extern "C" {
#endif

extern ComPtr<IDXGISwapChain3> avdl_swapChain;
extern ComPtr<ID3D11DeviceContext3> avdl_d3dContext;
extern ComPtr<ID3D11RenderTargetView1> avdl_d3dRenderTargetView;

extern int dd_flag_exit;

int avdl_engine_init(struct avdl_engine *o) {

	o->isPaused = 1;
	o->cworld = 0;
	o->nworld = 0;
	//o->nworld_ready = 0;
	nworld_ready = 0;
	o->nworld_loading = 0;
	o->nworld_size = 0;
	o->nworld_constructor = 0;

	o->input_key = 0;

	/*
	#ifdef AVDL_STEAM
	if (!o->verify) {
		if (!avdl_steam_init()) {
			dd_log("avdl: error initialising steam");
			return -1;
		}
	}
	#endif
	*/

	avdl_input_Init(&o->input);

	/*
	#if defined(AVDL_DIRECT3D11)
	#elif defined(_WIN32) || defined(WIN32)
	const PROJ_LOC_TYPE *proj_loc = avdl_getProjectLocation();
	if (proj_loc) {
		if (_wchdir(proj_loc) != 0) {
			dd_log("avdl: failed to change directory: %lS", _wcserror(errno));
			return -1;
		}
	}
	else {
		dd_log("avdl error: unable to get project location");
	}
	#endif
	*/

	o->achievements = avdl_achievements_create();
	avdl_assetManager_init();

	#if DD_PLATFORM_NATIVE
	/*
	// initialise curl
	curl_global_init(CURL_GLOBAL_ALL);

	if (pthread_mutex_init(&asyncCallMutex, NULL) != 0)
	{
		dd_log("avdl: mutex for async calls init failed");
		return -1;
	}
	*/
	#endif

	// initialise pre-game data to defaults then to game-specifics
	dd_gameInitDefault();
	dd_gameInit();


	#if DD_PLATFORM_NATIVE || defined(AVDL_DIRECT3D11)
	avdl_engine_resize(o, dd_window_width(), dd_window_height());
	#endif

	avdl_graphics_Init();

	/*
	 * string3d initialisation for displaying text
	 */
	if (dd_string3d_isActive()) {
		dd_string3d_init();
	}

	dd_clearColour(0.6f, 0.9f, 0.2f);

	return 0;
}

extern "C" struct dd_matrix matPerspective;
extern "C" void avdl_graphics_direct3d11_drawMesh(struct dd_matrix *matrix);

int avdl_engine_draw(struct avdl_engine *o) {

	// render here with direct 3d

	// clear previous frame
	avdl_graphics_ClearToColour();
	avdl_graphics_ClearColourAndDepth();

	// reset view
	dd_matrix_globalInit();

	// Reset render targets to the screen.
	ID3D11RenderTargetView *const targets[1] = { avdl_d3dRenderTargetView.Get() };
	avdl_d3dContext->OMSetRenderTargets(1, targets, 0);

	// draw world
	if (o->cworld && o->cworld->draw) {
		o->cworld->draw(o->cworld);
	}

	/*
	 * ??
	 */
	// Prepare the constant buffer to send it to the graphics device.
	avdl_d3dContext->UpdateSubresource1(
		avdl_constantBuffer.Get(),
		0,
		NULL,
		&avdl_constantBufferData,
		0,
		0,
		0
	);

	// Each vertex is one instance of the VertexPositionColor struct.
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	avdl_d3dContext->IASetVertexBuffers(
		0,
		1,
		avdl_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
	);

	avdl_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	avdl_d3dContext->IASetInputLayout(avdl_inputLayout.Get());

	// Attach our vertex shader.
	avdl_d3dContext->VSSetShader(
		avdl_vertexShader.Get(),
		nullptr,
		0
	);

	// Send the constant buffer to the graphics device.
	avdl_d3dContext->VSSetConstantBuffers1(
		0,
		1,
		avdl_constantBuffer.GetAddressOf(),
		nullptr,
		nullptr
		);

	// Attach our pixel shader.
	avdl_d3dContext->PSSetShader(
		avdl_pixelShader.Get(),
		nullptr,
		0
		);
	
	// Draw cube
	avdl_d3dContext->Draw(
		9,
		0
	);

	// The first argument instructs DXGI to block until VSync, putting the application
	// to sleep until the next VSync. This ensures we don't waste any cycles rendering
	// frames that will never be displayed to the screen.
	DXGI_PRESENT_PARAMETERS parameters = { 0 };
	HRESULT hr = avdl_swapChain->Present1(1, 0, &parameters);

	// Discard the contents of the render target.
	// This is a valid operation only when the existing contents will be entirely
	// overwritten. If dirty or scroll rects are used, this call should be removed.
	avdl_d3dContext->DiscardView1(avdl_d3dRenderTargetView.Get(), nullptr, 0);

	return 0;

}

int avdl_engine_loop(struct avdl_engine *o) {
	/*
	// run the message loop
	int isRunning = 1;
	MSG msg = {};
	while (isRunning) {

		// get msg
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// msg to quit
		if (msg.message == WM_QUIT) {
			break;
		}

		//update();

		#if DD_PLATFORM_NATIVE
		if (avdl_engine_isPaused(o)) {
			return 0;
		}
		#endif
		avdl_engine_update(o);

		// prepare next frame
		#if DD_PLATFORM_NATIVE
		//draw();
		#endif

		#if DD_PLATFORM_ANDROID
		if (dd_flag_exit) {
			return 0;
		}
		#endif

		#if DD_PLATFORM_NATIVE
		avdl_engine_draw(o);
		#endif

		// close the game
		if (dd_flag_exit) {
//			JNIEnv *env;
//			int getEnvStat = (*jvm)->GetEnv(jvm, &env, JNI_VERSION_1_4);
//
//			if (getEnvStat == JNI_EDETACHED) {
//				if ((*jvm)->AttachCurrentThread(jvm, &env, NULL) != 0) {
//					dd_log("avdl: failed to attach thread for new world");
//				}
//			} else if (getEnvStat == JNI_OK) {
//			} else if (getEnvStat == JNI_EVERSION) {
//				dd_log("avdl: GetEnv: version not supported");
//			}
//			jniEnv = env;
//			dd_log("get method");
//			jmethodID MethodID = (*(*jniEnv)->GetStaticMethodID)(jniEnv, clazz, "CloseApplication", "()V");
//			dd_log("call method");
//			(*(*jniEnv)->CallStaticVoidMethod)(jniEnv, clazz, MethodID);
//			dd_log("detach");
//			if (getEnvStat == JNI_EDETACHED) {
//				(*jvm)->DetachCurrentThread(jvm);
//			}
		}
	}
	*/
	return 0;
}

#ifdef __cplusplus
}
#endif

#endif
