#include "pch.h"
#include "App.h"

#include <ppltasks.h>
#include "..\avdl_engine.h"
#include "dd_game.h"
#include "dd_matrix.h"

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
extern "C" ComPtr<ID3D11Device3> avdl_d3dDevice;
extern "C" ComPtr<ID3D11DeviceContext3> avdl_d3dContext;
extern "C" ComPtr<ID3D11RenderTargetView1> avdl_d3dRenderTargetView;

// mesh
ComPtr<ID3D11Buffer> avdl_constantBuffer;
ModelViewProjectionConstantBuffer avdl_constantBufferData;

ComPtr<ID3D11Buffer> avdl_vertexBuffer;

// shaders
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
	// prepare avdl
	avdl_engine_init(&engine);

	// Prepare lifecycle handlers
	applicationView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &D3D11AvdlApplication::OnActivated);
	CoreApplication::Suspending += ref new EventHandler<SuspendingEventArgs^>(this, &D3D11AvdlApplication::OnSuspending);
	CoreApplication::Resuming   += ref new EventHandler<Platform::Object^>   (this, &D3D11AvdlApplication::OnResuming);


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

	avdl_graphics_d3d11_SetWindow();
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
		{XMFLOAT3( 0.5f, -0.5f,  0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{XMFLOAT3(-0.5f, -0.5f,  0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{XMFLOAT3( 0.0f,  0.5f,  0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f)},

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

	/*
	 * potentially handle orientations ?
	*/
	struct dd_matrix orientation;
	dd_matrix_identity(&orientation);
	XMMATRIX orientationMatrix = XMLoadFloat4x4((DirectX::XMFLOAT4X4 *)orientation.cell);

	XMStoreFloat4x4(
		&avdl_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix)
	);
//	XMStoreFloat4x4(
//		&avdl_constantBufferData.projection,
//		XMLoadFloat4x4((DirectX::XMFLOAT4X4 *)orientation.cell)
//	);

	XMStoreFloat4x4(&avdl_constantBufferData.view, XMLoadFloat4x4((DirectX::XMFLOAT4X4 *) orientation.cell));

	avdl_engine_initWorld(&engine, dd_default_world_constructor, dd_default_world_size);
	avdl_engine_setPaused(&engine, false);
}

extern struct dd_matrix matPerspective;

// This method is called after the window becomes active.
void D3D11AvdlApplication::Run()
{
	while (1)
	{
		// window events
		//Window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
		CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

		// Convert degrees to radians, then convert seconds to rotation angle
		struct dd_matrix m;
		dd_matrix_identity(&m);
		//dd_matrix_copy(&m, &matPerspective);

		float radiansPerSecond = 1;
		totalRotation += radiansPerSecond *0.001;
		float radians = static_cast<float>(fmod(totalRotation, XM_2PI));
		dd_matrix_translate(&m, 0, 0, -5);
		dd_matrix_rotate(&m, totalRotation *1000, 0, 1, 0);

		XMMATRIX d3d11Mat = XMLoadFloat4x4((DirectX::XMFLOAT4X4 *)m.cell);
		XMStoreFloat4x4(&avdl_constantBufferData.model, d3d11Mat);

		// avdl update
		avdl_engine_update(&engine);

		// avdl render
		avdl_engine_draw(&engine);
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
	/*
	CoreWindow^ Window = CoreWindow::GetForCurrentThread();
	// Set the 3D rendering viewport to target the entire window.
	D3D11_VIEWPORT avdl_screenViewport = CD3D11_VIEWPORT(
		0.0f,
		0.0f,
		Window->Bounds.Width,
		Window->Bounds.Height
		);

	avdl_d3dContext->RSSetViewports(1, &avdl_screenViewport);
	*/
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
