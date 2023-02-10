#include "GameWindow.h"
#include "imgui/imgui.h"
#include "spdlog/spdlog.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "EngineMacros.h"

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
	glfwSetFramebufferSizeCallback(window, OnFrameBufferSizeChanged);

	if (glewInit() != GLEW_OK)
		spdlog::error("glew init failed.");
}

void Nuwa::GameWindow::OnStart()
{
	float positions[] =
	{
		0.5f, 0.5f, 0.0f,   // срио╫г
		0.5f, -0.5f, 0.0f,  // сроб╫г
		-0.5f, -0.5f, 0.0f, // вСоб╫г
		-0.5f, 0.5f, 0.0f   // вСио╫г
	};

	uint indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	vao = new VertexArray();
	vbo = new VertexBuffer(positions, sizeof(positions));

	VertexLayout layout;
	layout.Push<float>(3);

	vao->AddBuffer(*vbo, layout);

	ibo = new IndexBuffer(indices, sizeof(indices));

	shader = new Shader("Resources/Shaders/Default.shader");
	shader->Bind();
}

void Nuwa::GameWindow::OnGUI()
{
	//ImGui::ShowDemoWindow();
}

void Nuwa::GameWindow::OnUpdate()
{
}

void Nuwa::GameWindow::OnRenderObject()
{
	renderer->Draw(vao, ibo, shader);
}

void Nuwa::GameWindow::OnFrameBufferSizeChanged(GLFWwindow* window, int width, int height)
{
	GL_ASSERT(glViewport(0, 0, width, height));
}
