#pragma once
#include "Core/NwWindow.h"

namespace Nuwa
{
	class GameWindow : public NwWindow
	{
	public:
		GameWindow(const WindowConfig& config);
		virtual ~GameWindow() {}

	protected:
		virtual void OnGUI() override;

		static void OnFrameBufferSizeChanged(GLFWwindow* window, int width, int height);
	};

}