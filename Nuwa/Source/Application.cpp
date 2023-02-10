#include "GameWindow.h"
#include "spdlog/spdlog.h"

int main(int argc, char** argv)
{
	spdlog::info("Nuwa startup.");

	Nuwa::GameWindow* window = new Nuwa::GameWindow({ 1366, 768, "Nuwa Framework", {0.5f, 0.5f, 0.5f, 1.0f} });
	window->InitImGui();

	spdlog::info("Game Window [{}] Created.", window->Title());
	spdlog::info("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	
	while (window->IsRun())
	{
		window->Update();
	}

	window->Close();
	glfwTerminate();

	return 0;
}