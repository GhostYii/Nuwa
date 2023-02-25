#include "NwWindow.h"
#include <GL/glew.h>
#include <spdlog/spdlog.h>

#include "../GUI.h"
#include "../EngineMacros.h"

Nuwa::NwWindow::NwWindow()
	:config({ 640, 480, false, "Nuwa Window", {1.0f,1.0f,1.0f,1.0f} }), window(nullptr)
{
	if (!glfwInit())
		spdlog::error("glfw init failed.");

	renderer = new ToyRenderer();
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

void Nuwa::NwWindow::Start()
{
	OnStart();
}

void Nuwa::NwWindow::Update()
{
	if (!window)
		return;

	GL_ASSERT(glClearColor(config.backgroundColor.r, config.backgroundColor.g, config.backgroundColor.b, config.backgroundColor.a));
	renderer->Clear();

	OnUpdate();
	OnRenderObject();

	Nuwa::BeginImGui();
	// gui code here
	OnGUI();
	Nuwa::RenderImGui(window, { config.backgroundColor.r, config.backgroundColor.g, config.backgroundColor.b, config.backgroundColor.a });

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Nuwa::NwWindow::Close()
{
	if (!window)
		return;

	Nuwa::EndImGui();
	glfwDestroyWindow(window);

}
