#include "GameWindow.h"
#include "spdlog/spdlog.h"

int main(int argc, char** argv)
{
	spdlog::info("Nuwa startup.");

	Nuwa::GameWindow* window = new Nuwa::GameWindow({ 1366, 768, "Nuwa Framework", {0.0f, 0.0f, 0.0f, 1.0f} });
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