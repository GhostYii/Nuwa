#pragma once
#include "Basic/NwWindow.h"
#include <memory>

#include "GameObject.h"

namespace Nuwa
{
	class GameWindow : public NwWindow
	{
	public:
		GameWindow(const WindowConfig& config);
		virtual ~GameWindow() {}

	protected:
		virtual void OnStart() override;
		virtual void OnGUI() override;
		virtual void OnUpdate() override;
		virtual void OnRenderObject() override;

		static void OnFrameBufferSizeChanged(GLFWwindow* window, int width, int height);

	private:
		// for test		
		GameObject* testGO;
		GameObject* camera;
	};

}