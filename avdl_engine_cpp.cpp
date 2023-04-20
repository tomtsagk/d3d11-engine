#include "avdl_engine.h"
#include <avdl_assetManager.h>
#include <dd_string3d.h>

#ifdef AVDL_DIRECT3D11
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

#ifdef __cplusplus
extern "C" {
#endif

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

int avdl_engine_draw(struct avdl_engine *o) {

	// render here with direct 3d
	/*
	float background_colour[4] = {
		0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f
	};
	device_context_ptr->ClearRenderTargetView(
		render_target_view_ptr, background_colour
	);
	*/
	/*
	avdl_graphics_ClearToColour();

	RECT winRect;
	GetClientRect(o->hwnd, &winRect);
	D3D11_VIEWPORT viewport = {
		0.0f,
		0.0f,
		(FLOAT)(winRect.right - winRect.left),
		(FLOAT)(winRect.bottom - winRect.top),
		0.0f,
		1.0f
	};
	device_context_ptr->RSSetViewports(1, &viewport);

	device_context_ptr->OMSetRenderTargets(1, &render_target_view_ptr, NULL);

	device_context_ptr->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	);
	device_context_ptr->IASetInputLayout(input_layout_ptr);
	device_context_ptr->IASetVertexBuffers(
		0,
		1,
		&vertex_buffer_ptr,
		&vertex_stride,
		&vertex_offset
	);

	device_context_ptr->VSSetShader(vertex_shader_ptr, NULL, 0);
	device_context_ptr->PSSetShader(pixel_shader_ptr, NULL, 0);

	device_context_ptr->Draw(vertex_count, 0);
	swap_chain_ptr->Present(1, 0);
	*/

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
