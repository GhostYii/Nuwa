#include "GameWindow.h"
#include "spdlog/spdlog.h"
#include "Global.h"

int main(int argc, char** argv)
{
	Nuwa::ReadGlobalValuesByConfig("nuwa.ini");
	spdlog::info("Nuwa startup.");

	Nuwa::Global::IsEditor = false;
#ifdef NUWA_EDITOR
	Nuwa::Global::IsEditor = true;
#endif // NUWA_EDITOR

	Nuwa::GameWindow* window = new Nuwa::GameWindow
	(
		{
			Nuwa::Global::Resolution.x,
			Nuwa::Global::Resolution.y,
			Nuwa::Global::IsFullScreen,
			"Nuwa Framework",
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		}
	);
	if (!window)
	{
		spdlog::error("Game Window create failed.");
		return -1;
	}

	window->InitImGui();

	spdlog::info("Game Window [{}] Created.", window->Title());
	spdlog::info("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

	window->Start();
	while (window->IsRun())
	{
		window->Update();
	}

	window->Close();
	glfwTerminate();

	return 0;
}