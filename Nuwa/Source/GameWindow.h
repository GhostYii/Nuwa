#pragma once
#include "Basic/NwWindow.h"
#include <memory>

#include "GameScene.h"

#ifdef NUWA_EDITOR
#include "Editor/Editor.h"

using namespace Nuwa::Editor;
#endif //NUWA_EDITOR

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
		static void OnWindowPositionChanged(GLFWwindow* window, int xpos, int ypos);

	private:
		GameScene* scene;

#ifdef NUWA_EDITOR
		EditorMode* editor;
#endif // NUWA_EDITOR
	};

}