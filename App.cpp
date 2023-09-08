#include "pch.h"
#include "App.h"

#include <ppltasks.h>
#include "..\avdl_engine.h"
#include <dd_game.h>

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

// Constant buffer used to send MVP matrices to the vertex shader.
struct ModelViewProjectionConstantBuffer
{
	DirectX::XMFLOAT4X4 model;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};

// Used to send per-vertex data to the vertex shader.
struct VertexPositionColor
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 color;
};

// parts of `avdl_graphics`
ComPtr<ID3D11Device1> dev;
ComPtr<ID3D11DeviceContext1> devcon;
ComPtr<IDXGISwapChain1> swapchain;
ComPtr<ID3D11RenderTargetView> rendertarget;

ComPtr<ID3D11Device3> avdl_d3dDevice;
ComPtr<ID3D11DeviceContext3> avdl_d3dContext;
ComPtr<IDXGISwapChain3> avdl_swapChain;
ComPtr<ID3D11RenderTargetView1>	avdl_d3dRenderTargetView;

// Constants used to calculate screen rotations
namespace ScreenRotation
{
	// 0-degree Z-rotation
	static const XMFLOAT4X4 Rotation0(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
};

// mesh
ComPtr<ID3D11Buffer> avdl_constantBuffer;
ModelViewProjectionConstantBuffer avdl_constantBufferData;

Size avdl_d3dRenderTargetSize;

// a struct to represent a single vertex
struct VERTEX
{
	float X, Y, Z;    // vertex position
};

ComPtr<ID3D11Buffer> vertexbuffer;    // defined in CGame
ComPtr<ID3D11Buffer> avdl_vertexBuffer;

// shaders
ComPtr<ID3D11VertexShader> vertexshader;
ComPtr<ID3D11PixelShader> pixelshader;
ComPtr<ID3D11InputLayout> inputlayout;

ComPtr<ID3D11VertexShader> avdl_vertexShader;
ComPtr<ID3D11PixelShader> avdl_pixelShader;
ComPtr<ID3D11InputLayout> avdl_inputLayout;

double totalRotation = 0.0;

extern "C" struct avdl_engine engine;

void avdl_log2(const char *msg, ...) {

	va_list args;
	va_start(args, msg);

	char buffer[1024];
	vsnprintf(buffer, 1024, msg, args);

	std::string s_str = std::string(buffer);
	std::wstring wid_str = std::wstring(s_str.begin(), s_str.end());
	const wchar_t* w_char = wid_str.c_str();
	Platform::String^ p_string = ref new Platform::String(w_char);

	MessageDialog^ dialog = ref new MessageDialog(p_string);
	UICommand^ continueCommand = ref new UICommand("Ok");
	UICommand^ upgradeCommand = ref new UICommand("Cancel");

	dialog->DefaultCommandIndex = 0;
	dialog->CancelCommandIndex = 1;
	dialog->Commands->Append(continueCommand);
	dialog->Commands->Append(upgradeCommand);
	dialog->ShowAsync();

	va_end(args);
}


#include <fstream>

// this function loads a file into an Array^
Array<byte>^ LoadShaderFile(std::string File)
{
	Array<byte>^ FileData = nullptr;

	// open the file
	std::ifstream VertexFile(File, std::ios::in | std::ios::binary | std::ios::ate);

	// if open was successful
	if(VertexFile.is_open())
	{
		// find the length of the file
		int Length = (int)VertexFile.tellg();

		// collect the file data
		FileData = ref new Array<byte>(Length);
		VertexFile.seekg(0, std::ios::beg);
		VertexFile.read(reinterpret_cast<char*>(FileData->Data), Length);
		VertexFile.close();
	}
	else {
	}

	return FileData;
}

// The main function is only used to initialize our IFrameworkView class.
[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
	CoreApplication::Run(ref new D3D11AvdlApplicationSource());
	return 0;
}

// Application Source
IFrameworkView^ D3D11AvdlApplicationSource::CreateView()
{
	return ref new D3D11AvdlApplication();
}

// The first method called when the IFrameworkView is being created.
void D3D11AvdlApplication::Initialize(CoreApplicationView^ applicationView)
{
	// Prepare lifecycle handlers
	applicationView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &D3D11AvdlApplication::OnActivated);
	CoreApplication::Suspending += ref new EventHandler<SuspendingEventArgs^>(this, &D3D11AvdlApplication::OnSuspending);
	CoreApplication::Resuming   += ref new EventHandler<Platform::Object^>   (this, &D3D11AvdlApplication::OnResuming);

	// This flag adds support for surfaces with a different color channel ordering
	// than the API default. It is required for compatibility with Direct2D.
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	/*
#if defined(_DEBUG)
	if (DX::SdkLayersAvailable())
	{
		// If the project is in a debug build, enable debugging via SDK Layers with this flag.
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}
#endif
*/

	// initialise avdl

	// Create the Direct3D 11 API device object and a corresponding context.
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	// Create the device and device context objects
	HRESULT hr = D3D11CreateDevice(
		nullptr, // adapter
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr, // software
		creationFlags, // flags
		nullptr, // feature levels
		0, // feature levels count
		D3D11_SDK_VERSION,
		&device, // device
		nullptr, // feature level variable
		&context // device context
	);

	// Store pointers to the Direct3D 11.3 API device and immediate context.
	device.As(&avdl_d3dDevice);
	context.As(&avdl_d3dContext);

	m_windowClosed = false;
}

// Called when the CoreWindow object is created (or re-created).
void D3D11AvdlApplication::SetWindow(CoreWindow^ window)
{
	// input
	window->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &D3D11AvdlApplication::OnPointerPressed);
	window->PointerMoved += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &D3D11AvdlApplication::OnPointerMoved);
	window->PointerReleased += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &D3D11AvdlApplication::OnPointerReleased);
	window->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &D3D11AvdlApplication::OnKeyDown);
	window->KeyUp += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &D3D11AvdlApplication::OnKeyUp);

	window->SizeChanged += 
		ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &D3D11AvdlApplication::OnWindowSizeChanged);

	window->VisibilityChanged +=
		ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &D3D11AvdlApplication::OnVisibilityChanged);

	// window event
	window->Closed += ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &D3D11AvdlApplication::OnWindowClosed);

	DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

	currentDisplayInformation->DpiChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &D3D11AvdlApplication::OnDpiChanged);

	currentDisplayInformation->OrientationChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &D3D11AvdlApplication::OnOrientationChanged);

	DisplayInformation::DisplayContentsInvalidated +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &D3D11AvdlApplication::OnDisplayContentsInvalidated);

	// Clear the previous window size specific context.
	ID3D11RenderTargetView* nullViews[] = {nullptr};
	avdl_d3dContext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
	avdl_d3dRenderTargetView = nullptr;
	avdl_d3dContext->Flush1(D3D11_CONTEXT_TYPE_ALL, nullptr);

	CoreWindow^ Window = CoreWindow::GetForCurrentThread();
	avdl_d3dRenderTargetSize.Width = Window->Bounds.Width;
	avdl_d3dRenderTargetSize.Height = Window->Bounds.Height;

	if (avdl_swapChain != nullptr)
	{
		// If the swap chain already exists, resize it.
		HRESULT hr = avdl_swapChain->ResizeBuffers(
			2, // Double-buffered swap chain.
			lround(avdl_d3dRenderTargetSize.Width),
			lround(avdl_d3dRenderTargetSize.Height),
			DXGI_FORMAT_B8G8R8A8_UNORM,
			0
		);
	}
	else
	{
		// Otherwise, create a new one using the same adapter as the existing Direct3D device.
		DXGI_SCALING scaling = DXGI_SCALING_NONE;
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {0};

		swapChainDesc.Width = lround(avdl_d3dRenderTargetSize.Width);		// Match the size of the window.
		swapChainDesc.Height = lround(avdl_d3dRenderTargetSize.Height);
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// This is the most common swap chain format.
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;								// Don't use multi-sampling.
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;									// Use double-buffering to minimize latency.
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	// All Microsoft Store apps must use this SwapEffect.
		swapChainDesc.Flags = 0;
		swapChainDesc.Scaling = scaling;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

		// This sequence obtains the DXGI factory that was used to create the Direct3D device above.
		ComPtr<IDXGIDevice3> dxgiDevice;
		avdl_d3dDevice.As(&dxgiDevice);

		ComPtr<IDXGIAdapter> dxgiAdapter;
		dxgiDevice->GetAdapter(&dxgiAdapter);

		ComPtr<IDXGIFactory4> dxgiFactory;
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

		ComPtr<IDXGISwapChain1> swapChain;
		dxgiFactory->CreateSwapChainForCoreWindow(
			avdl_d3dDevice.Get(),
			reinterpret_cast<IUnknown*>(window),
			&swapChainDesc,
			nullptr,
			&swapChain
		);
		swapChain.As(&avdl_swapChain);

		// Ensure that DXGI does not queue more than one frame at a time. This both reduces latency and
		// ensures that the application will only render after each VSync, minimizing power consumption.
		dxgiDevice->SetMaximumFrameLatency(1);
	}

	// Create a render target view of the swap chain back buffer.
	ComPtr<ID3D11Texture2D1> backBuffer;
	avdl_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

	avdl_d3dDevice->CreateRenderTargetView1(
		backBuffer.Get(),
		nullptr,
		&avdl_d3dRenderTargetView
	);

	// Set the 3D rendering viewport to target the entire window.
	D3D11_VIEWPORT avdl_screenViewport = CD3D11_VIEWPORT(
		0.0f,
		0.0f,
		Window->Bounds.Width,
		Window->Bounds.Height
		);

	avdl_d3dContext->RSSetViewports(1, &avdl_screenViewport);

	// Create window size dependent resources
	/*
	CoreWindow^ Window = CoreWindow::GetForCurrentThread();
	float aspectRatio = Window->Bounds.Width /Window->Bounds.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}

	// Note that the OrientationTransform3D matrix is post-multiplied here
	// in order to correctly orient the scene to match the display orientation.
	// This post-multiplication step is required for any draw calls that are
	// made to the swap chain render target. For draw calls to other targets,
	// this transform should not be applied.

	// This sample makes use of a right-handed coordinate system using row-major matrices.
	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
		);

	XMFLOAT4X4 orientation = ScreenRotation::Rotation0;

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	XMStoreFloat4x4(
		&avdl_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	// Eye is at (0,0.7,1.5), looking at point (0,-0.1,0) with the up-vector along the y-axis.
	static const XMVECTORF32 eye = { 0.0f, 0.7f, 1.5f, 0.0f };
	static const XMVECTORF32 at = { 0.0f, -0.1f, 0.0f, 0.0f };
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	XMStoreFloat4x4(&avdl_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
	//avdl_log2("scene renderer create window size dependent resources");
	*/
}

// Initializes scene resources, or loads a previously saved app state.
void D3D11AvdlApplication::Load(Platform::String^ entryPoint)
{
	Array<byte>^ VSFile = LoadShaderFile("SampleVertexShader.cso");
	Array<byte>^ PSFile = LoadShaderFile("SamplePixelShader.cso");
	avdl_d3dDevice->CreateVertexShader(
		VSFile->Data,
		VSFile->Length,
		nullptr,
		&avdl_vertexShader
	);
	avdl_d3dDevice->CreatePixelShader(
		PSFile->Data,
		PSFile->Length,
		nullptr,
		&avdl_pixelShader
	);

	static const D3D11_INPUT_ELEMENT_DESC vertexDesc [] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	avdl_d3dDevice->CreateInputLayout(
		vertexDesc,
		ARRAYSIZE(vertexDesc),
		VSFile->Data,
		VSFile->Length,
		&avdl_inputLayout
	);

	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
	avdl_d3dDevice->CreateBuffer(
		&constantBufferDesc,
		nullptr,
		&avdl_constantBuffer
	);

	// Load mesh vertices. Each vertex has a position and a color.
	static const VertexPositionColor cubeVertices[] = 
	{
		{XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f)},

		{XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
		{XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
		{XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f)},

		{XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3(0.7f, 0.5f, 0.5f)},
		{XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3(0.5f, 0.7f, 0.5f)},
		{XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.5f, 0.5f, 0.7f)},
	};

	D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
	vertexBufferData.pSysMem = cubeVertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
	avdl_d3dDevice->CreateBuffer(
		&vertexBufferDesc,
		&vertexBufferData,
		&avdl_vertexBuffer
	);

	CoreWindow^ Window = CoreWindow::GetForCurrentThread();
	float aspectRatio = Window->Bounds.Width /Window->Bounds.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}

	// Note that the OrientationTransform3D matrix is post-multiplied here
	// in order to correctly orient the scene to match the display orientation.
	// This post-multiplication step is required for any draw calls that are
	// made to the swap chain render target. For draw calls to other targets,
	// this transform should not be applied.

	// This sample makes use of a right-handed coordinate system using row-major matrices.
	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
		);

	XMFLOAT4X4 orientation = ScreenRotation::Rotation0;

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	XMStoreFloat4x4(
		&avdl_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	// Eye is at (0,0.7,1.5), looking at point (0,-0.1,0) with the up-vector along the y-axis.
	static const XMVECTORF32 eye = { 0.0f, 0.7f, 1.5f, 0.0f };
	static const XMVECTORF32 at = { 0.0f, -0.1f, 0.0f, 0.0f };
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	XMStoreFloat4x4(&avdl_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
	//avdl_log2("scene renderer create window size dependent resources");

	avdl_engine_init(&engine);
	avdl_engine_initWorld(&engine, dd_default_world_constructor, dd_default_world_size);
	avdl_engine_setPaused(&engine, false);
}

// This method is called after the window becomes active.
void D3D11AvdlApplication::Run()
{
//	/*
//	 * Triangle
//	 */
//	// create a triangle out of vertices
//	VERTEX OurVertices[] =
//	{
//		{ 0.0f, 0.5f, 0.0f },
//		{ 0.45f, -0.5f, 0.0f },
//		{ -0.45f, -0.5f, 0.0f },
//	};
//
//	// create the vertex buffer
//	D3D11_BUFFER_DESC bd = {0};
//	bd.ByteWidth = sizeof(VERTEX) * ARRAYSIZE(OurVertices);
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//
//	D3D11_SUBRESOURCE_DATA srd = {OurVertices, 0, 0};
//
//	dev->CreateBuffer(&bd, &srd, &vertexbuffer);
//
//	/*
//	 * shaders
//	 */
//	// set the shader objects as the active shaders
//	devcon->VSSetShader(vertexshader.Get(), nullptr, 0);
//	devcon->PSSetShader(pixelshader.Get(), nullptr, 0);
//	devcon->IASetInputLayout(inputlayout.Get());

	float r = 0;
	while (1)
	{
		r += 0.01;
		if (r > 1) {
			r -= 1.0;
		}
		//if (m_windowVisible)
		//{
			// window events
			//Window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

			// avdl update
			// Convert degrees to radians, then convert seconds to rotation angle
			float radiansPerSecond = XMConvertToRadians(45);
			totalRotation += radiansPerSecond *0.1;
			float radians = static_cast<float>(fmod(totalRotation, XM_2PI));
			XMStoreFloat4x4(&avdl_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(radians)));
			avdl_engine_update(&engine);

			// avdl render
			// Clear Color
			XMVECTORF32 clearcolor = { dd_clearcolor_r, dd_clearcolor_g, dd_clearcolor_b, 0.0f };
			avdl_d3dContext->ClearRenderTargetView(avdl_d3dRenderTargetView.Get(), clearcolor);

			// Reset render targets to the screen.
			ID3D11RenderTargetView *const targets[1] = { avdl_d3dRenderTargetView.Get() };
			avdl_d3dContext->OMSetRenderTargets(1, targets, 0);

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
		
			// Draw the objects.
			avdl_d3dContext->Draw(
				9,
				0
				);
			avdl_engine_draw(&engine);

			//m_deviceResources->Present();
			// The first argument instructs DXGI to block until VSync, putting the application
			// to sleep until the next VSync. This ensures we don't waste any cycles rendering
			// frames that will never be displayed to the screen.
			DXGI_PRESENT_PARAMETERS parameters = { 0 };
			HRESULT hr = avdl_swapChain->Present1(1, 0, &parameters);

			// Discard the contents of the render target.
			// This is a valid operation only when the existing contents will be entirely
			// overwritten. If dirty or scroll rects are used, this call should be removed.
			avdl_d3dContext->DiscardView1(avdl_d3dRenderTargetView.Get(), nullptr, 0);

			/*
			// set our new render target object as the active render target
			devcon->OMSetRenderTargets(1, rendertarget.GetAddressOf(), nullptr);

			// clear the back buffer to a deep blue
			float color[4] = {r, 0.2f, 0.4f, 1.0f};
			devcon->ClearRenderTargetView(rendertarget.Get(), color);

			/*
			 * Render triangle
			 *
			// set the vertex buffer
			UINT stride = sizeof(VERTEX);
			UINT offset = 0;
			devcon->IASetVertexBuffers(0, 1, vertexbuffer.GetAddressOf(), &stride, &offset);

			// set the primitive topology
			devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// set input layout ?
			devcon->IASetInputLayout(inputlayout.Get());

			// re-set shaders ?
			devcon->VSSetShader(vertexshader.Get(), nullptr, 0);
			devcon->PSSetShader(pixelshader.Get(), nullptr, 0);

			// draw 3 vertices, starting from vertex 0
			devcon->Draw(3, 0);

			// switch the back buffer and the front buffer
			swapchain->Present(1, 0);
			*/
			/*
		}
		else
		{
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
		}
		*/
	}
}

// Required for IFrameworkView.
// Terminate events do not cause Uninitialize to be called. It will be called if your IFrameworkView
// class is torn down while the app is in the foreground.
void D3D11AvdlApplication::Uninitialize()
{
}

// Application lifecycle event handlers.

void D3D11AvdlApplication::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
{
	// Run() won't start until the CoreWindow is activated.
	CoreWindow::GetForCurrentThread()->Activate();
}

void D3D11AvdlApplication::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
}

void D3D11AvdlApplication::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
}

void D3D11AvdlApplication::OnPointerPressed(CoreWindow^ window, PointerEventArgs^ args) {
	//MessageDialog Dialog("Pointer pressed", "Input detected");
	//Dialog.ShowAsync();
}

void D3D11AvdlApplication::OnPointerMoved(CoreWindow^ window, PointerEventArgs^ args) {
}

void D3D11AvdlApplication::OnPointerReleased(CoreWindow^ window, PointerEventArgs^ args) {
}

void D3D11AvdlApplication::OnKeyDown(CoreWindow^ window, KeyEventArgs^ args) {
	if(args->VirtualKey == VirtualKey::A)
	{
	}
	else
	if(args->VirtualKey == VirtualKey::GamepadA)
	{
	}
	else {
	}
}

void D3D11AvdlApplication::OnKeyUp(CoreWindow^ window, KeyEventArgs^ args) {
	// keyboard A
	if(args->VirtualKey == VirtualKey::A)
	{
	}
	else
	// gamepad A
	if(args->VirtualKey == VirtualKey::GamepadA)
	{
	}
	else {
	}
}

// Window event handlers.

void D3D11AvdlApplication::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
{
}

void D3D11AvdlApplication::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
}

void D3D11AvdlApplication::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	m_windowClosed = true;
}

// DisplayInformation event handlers.

void D3D11AvdlApplication::OnDpiChanged(DisplayInformation^ sender, Object^ args)
{
}

void D3D11AvdlApplication::OnOrientationChanged(DisplayInformation^ sender, Object^ args)
{
}

void D3D11AvdlApplication::OnDisplayContentsInvalidated(DisplayInformation^ sender, Object^ args)
{
}
