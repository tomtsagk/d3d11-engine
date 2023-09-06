#include "pch.h"
#include "App.h"

#include <ppltasks.h>

using namespace App2_uwp_dx11;

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

// parts of `avdl_graphics`
ComPtr<ID3D11Device1> dev;
ComPtr<ID3D11DeviceContext1> devcon;
ComPtr<IDXGISwapChain1> swapchain;
ComPtr<ID3D11RenderTargetView> rendertarget;

// a struct to represent a single vertex
struct VERTEX
{
	float X, Y, Z;    // vertex position
};

ComPtr<ID3D11Buffer> vertexbuffer;    // defined in CGame

// shaders
ComPtr<ID3D11VertexShader> vertexshader;
ComPtr<ID3D11PixelShader> pixelshader;
ComPtr<ID3D11InputLayout> inputlayout;

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
		MessageDialog Dialog("Error opening shaders", "AA");
		Dialog.ShowAsync();
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

	// At this point we have access to the device. 
	// We can create the device-dependent resources.
	//m_deviceResources = std::make_shared<DX::DeviceResources>();

	m_windowClosed = false;
	m_windowVisible = true;
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

	//m_deviceResources->SetWindow(window);
}

// Initializes scene resources, or loads a previously saved app state.
void D3D11AvdlApplication::Load(Platform::String^ entryPoint)
{
	/*
	if (m_main == nullptr)
	{
		m_main = std::unique_ptr<App2_uwp_dx11Main>(new App2_uwp_dx11Main(m_deviceResources));
	}
	*/
}

// This method is called after the window becomes active.
void D3D11AvdlApplication::Run()
{
	// initialise avdl

	// Define temporary pointers to a device and a device context
	ComPtr<ID3D11Device> dev11;
	ComPtr<ID3D11DeviceContext> devcon11;

	// Create the device and device context objects
	D3D11CreateDevice(
		nullptr, // adapter
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr, // software
		0, // flags
		nullptr, // feature levels
		0, // feature levels count
		D3D11_SDK_VERSION,
		&dev11, // device
		nullptr, // feature level variable
		&devcon11 // device context
	);

	// Convert the pointers from the DirectX 11 versions to the DirectX 11.1 versions
	dev11.As(&dev);
	devcon11.As(&devcon);

	/*
	 * Get Factory
	 */
	// First, convert our ID3D11Device1 into an IDXGIDevice1
	ComPtr<IDXGIDevice1> dxgiDevice;
	dev.As(&dxgiDevice);

	// Second, use the IDXGIDevice1 interface to get access to the adapter
	ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(&dxgiAdapter);

	// Third, use the IDXGIAdapter interface to get access to the factory
	ComPtr<IDXGIFactory2> dxgiFactory;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), &dxgiFactory);

	/*
	 * Swap chain
	 */
	// set up the swap chain description
	DXGI_SWAP_CHAIN_DESC1 scd = {0};
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // how the swap chain should be used
	scd.BufferCount = 2;                                  // a front buffer and a back buffer
	scd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;              // the most common swap chain format
	scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;    // the recommended flip mode
	scd.SampleDesc.Count = 1;                             // disable anti-aliasing

	// swapchain creation
	CoreWindow^ Window = CoreWindow::GetForCurrentThread();    // get the window pointer

	dxgiFactory->CreateSwapChainForCoreWindow(
		dev.Get(),                                  // address of the device
		reinterpret_cast<IUnknown*>(Window),        // address of the window
		&scd,                                       // address of the swap chain description
		nullptr,                                    // advanced
		&swapchain                                // address of the new swap chain pointer
	);

	/*
	 * set render target
	 */
	// get a pointer directly to the back buffer
	ComPtr<ID3D11Texture2D> backbuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backbuffer);

	// create a render target pointing to the back buffer
	dev->CreateRenderTargetView(backbuffer.Get(), nullptr, &rendertarget);

	/*
	 * View port
	 */
	// set the viewport
	D3D11_VIEWPORT viewport = {0};

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = Window->Bounds.Width;
	viewport.Height = Window->Bounds.Height;

	devcon->RSSetViewports(1, &viewport);

	/*
	 * Triangle
	 */
	// create a triangle out of vertices
	VERTEX OurVertices[] =
	{
		{ 0.0f, 0.5f, 0.5f },
		{ 0.45f, -0.5f, 0.5f },
		{ -0.45f, -0.5f, 0.5f },
	};

	// create the vertex buffer
	D3D11_BUFFER_DESC bd = {0};
	bd.ByteWidth = sizeof(VERTEX) * ARRAYSIZE(OurVertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA srd = {OurVertices, 0, 0};

	dev->CreateBuffer(&bd, &srd, &vertexbuffer);

	/*
	 * shaders
	 */
	Array<byte>^ VSFile = LoadShaderFile("VertexShader.cso");
	Array<byte>^ PSFile = LoadShaderFile("PixelShader.cso");

	// create the shader objects
	dev->CreateVertexShader(VSFile->Data, VSFile->Length, nullptr, &vertexshader);
	dev->CreatePixelShader(PSFile->Data, PSFile->Length, nullptr, &pixelshader);

	// set the shader objects as the active shaders
	devcon->VSSetShader(vertexshader.Get(), nullptr, 0);
	devcon->PSSetShader(pixelshader.Get(), nullptr, 0);

	// initialize input layout
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	// create and set the input layout
	dev->CreateInputLayout(ied, ARRAYSIZE(ied), VSFile->Data, VSFile->Length, &inputlayout);
	devcon->IASetInputLayout(inputlayout.Get());

	float r = 0;
	while (!m_windowClosed)
	{
		r += 0.01;
		if (r > 0) {
			r -= 1.0;
		}
		//if (m_windowVisible)
		//{
			// window events
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

			// avdl update

			// avdl render
			/*
			// game update
			m_main->Update();

			// game render
			if (m_main->Render())
			{
				m_deviceResources->Present();
			}
			*/
			// set our new render target object as the active render target
			devcon->OMSetRenderTargets(1, rendertarget.GetAddressOf(), nullptr);

			// clear the back buffer to a deep blue
			float color[4] = {r, 0.2f, 0.4f, 1.0f};
			devcon->ClearRenderTargetView(rendertarget.Get(), color);

			/*
			 * Render triangle
			 */
			// set the vertex buffer
			UINT stride = sizeof(VERTEX);
			UINT offset = 0;
			devcon->IASetVertexBuffers(0, 1, vertexbuffer.GetAddressOf(), &stride, &offset);

			// set the primitive topology
			devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// draw 3 vertices, starting from vertex 0
			devcon->Draw(3, 0);

			// switch the back buffer and the front buffer
			swapchain->Present(1, 0);
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
	// Save app state asynchronously after requesting a deferral. Holding a deferral
	// indicates that the application is busy performing suspending operations. Be
	// aware that a deferral may not be held indefinitely. After about five seconds,
	// the app will be forced to exit.
	SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

	create_task([this, deferral]()
	{
		//m_deviceResources->Trim();

		// Insert your code here.

		deferral->Complete();
	});
}

void D3D11AvdlApplication::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
	// Restore any data or state that was unloaded on suspend. By default, data
	// and state are persisted when resuming from suspend. Note that this event
	// does not occur if the app was previously terminated.

	// Insert your code here.
}

void D3D11AvdlApplication::OnPointerPressed(CoreWindow^ window, PointerEventArgs^ args) {
	MessageDialog Dialog("Pointer pressed", "Input detected");
	Dialog.ShowAsync();
}

void D3D11AvdlApplication::OnPointerMoved(CoreWindow^ window, PointerEventArgs^ args) {
}

void D3D11AvdlApplication::OnPointerReleased(CoreWindow^ window, PointerEventArgs^ args) {
}

void D3D11AvdlApplication::OnKeyDown(CoreWindow^ window, KeyEventArgs^ args) {
	if(args->VirtualKey == VirtualKey::A)
	{
		MessageDialog Dialog("Key 'A' pressed", "Input detected");
		Dialog.ShowAsync();
	}
	else
	if(args->VirtualKey == VirtualKey::GamepadA)
	{
		MessageDialog Dialog("Gamepad 'A' pressed", "Input detected");
		Dialog.ShowAsync();
	}
	else {
		MessageDialog Dialog("Unknown key pressed", "Input detected");
		Dialog.ShowAsync();
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
	//m_deviceResources->SetLogicalSize(Size(sender->Bounds.Width, sender->Bounds.Height));
	//m_main->CreateWindowSizeDependentResources();
}

void D3D11AvdlApplication::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	m_windowVisible = args->Visible;
}

void D3D11AvdlApplication::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	m_windowClosed = true;
}

// DisplayInformation event handlers.

void D3D11AvdlApplication::OnDpiChanged(DisplayInformation^ sender, Object^ args)
{
	// Note: The value for LogicalDpi retrieved here may not match the effective DPI of the app
	// if it is being scaled for high resolution devices. Once the DPI is set on DeviceResources,
	// you should always retrieve it using the GetDpi method.
	// See DeviceResources.cpp for more details.
	//m_deviceResources->SetDpi(sender->LogicalDpi);
	//m_main->CreateWindowSizeDependentResources();
}

void D3D11AvdlApplication::OnOrientationChanged(DisplayInformation^ sender, Object^ args)
{
	//m_deviceResources->SetCurrentOrientation(sender->CurrentOrientation);
	//m_main->CreateWindowSizeDependentResources();
}

void D3D11AvdlApplication::OnDisplayContentsInvalidated(DisplayInformation^ sender, Object^ args)
{
	//m_deviceResources->ValidateDevice();
}
