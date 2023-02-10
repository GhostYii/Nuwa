#include "GameWindow.h"
#include "imgui/imgui.h"
#include "spdlog/spdlog.h"

Nuwa::GameWindow::GameWindow(const WindowConfig& config)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->config = config;
	window = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);

	if (!window)
	{
		spdlog::error("Window \"{}\" create failed.", config.title);
		return;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		spdlog::error("glew init failed.");
}

void Nuwa::GameWindow::OnGUI()
{
	//ImGui::ShowDemoWindow();
}
