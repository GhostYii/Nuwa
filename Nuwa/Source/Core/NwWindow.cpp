#include "NwWindow.h"
#include <GL/glew.h>
#include "../GUI/GUI.h"
#include <spdlog/spdlog.h>

Nuwa::NwWindow::NwWindow()
	:config({ 640, 480, "Nuwa Window", {0.5f,0.5f,0.5f,1.0f} }), window(nullptr)
{
	if (!glfwInit())
		spdlog::error("glfw init failed.");
}

Nuwa::NwWindow::~NwWindow()
{
	Close();
	glfwTerminate();
}

bool Nuwa::NwWindow::IsRun()
{
	return !glfwWindowShouldClose(window);
}

void Nuwa::NwWindow::InitImGui()
{
	if (!window)
		return;

	Nuwa::InitImGui(window);
}

void Nuwa::NwWindow::Update()
{
	if (!window)
		return;

	glfwPollEvents();
	Nuwa::BeginImGui();

	// gui code here
	OnGUI();

	Nuwa::RenderImGui(window, { config.backgroundColor.x, config.backgroundColor.y, config.backgroundColor.z, config.backgroundColor.w });
	glfwSwapBuffers(window);
}

void Nuwa::NwWindow::Close()
{
	if (!window)
		return;

	Nuwa::EndImGui();
	glfwDestroyWindow(window);

}
