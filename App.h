﻿#pragma once

#include "pch.h"

// Main d3d11 avdl application
ref class D3D11AvdlApplication sealed : public Windows::ApplicationModel::Core::IFrameworkView
{
public:
	// must-override functions
	virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
	virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
	virtual void Load(Platform::String^ entryPoint);
	virtual void Run();
	virtual void Uninitialize();

protected:

	// lifecycle events
	void OnActivated(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args);
	void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
	void OnResuming(Platform::Object^ sender, Platform::Object^ args);

	// input
	void OnPointerPressed(Windows::UI::Core::CoreWindow^ window, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerMoved(Windows::UI::Core::CoreWindow^ window, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerReleased(Windows::UI::Core::CoreWindow^ window, Windows::UI::Core::PointerEventArgs^ args);
	void OnKeyDown(Windows::UI::Core::CoreWindow^ window, Windows::UI::Core::KeyEventArgs^ args);
	void OnKeyUp(Windows::UI::Core::CoreWindow^ window, Windows::UI::Core::KeyEventArgs^ args);

	// Window event handlers.
	void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
	void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);
	void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);

	// DisplayInformation event handlers.
	void OnDpiChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
	void OnOrientationChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
	void OnDisplayContentsInvalidated(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);

private:
	bool m_windowClosed;
};

// Application Source
ref class D3D11AvdlApplicationSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
{
public:
	virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();
};
