#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"

// Renders Direct2D and 3D content on the screen.
namespace App2_uwp_dx11
{
	class App2_uwp_dx11Main
	{
	public:
		App2_uwp_dx11Main(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~App2_uwp_dx11Main();
		void CreateWindowSizeDependentResources();
		void Update();
		bool Render();

	private:
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: Replace with your own content renderers.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;

		// Rendering loop timer.
		DX::StepTimer m_timer;
	};
}
