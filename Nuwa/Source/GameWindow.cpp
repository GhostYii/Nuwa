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
		100.0f, 100.0f, 0.0f, 0.0f,  // 0
		200.0f, 100.0f, 1.0f, 0.0f,  // 1
		200.0f, 200.0f, 1.0f, 1.0f,  // 2
		100.0f, 200.0f, 0.0f, 1.0f   // 3
	};

	uint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GL_ASSERT(glEnable(GL_BLEND));
	GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	vao = new VertexArray();
	vbo = new VertexBuffer(positions, sizeof(positions));

	VertexLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);

	vao->AddBuffer(*vbo, layout);

	ibo = new IndexBuffer(indices, sizeof(indices));

	shader = new Shader("Resources/Shaders/Default.shader");
	shader->Bind();	
	shader->SetInt("tex", 0);

	texture = new Texture("Resources/Textures/nuwa.png");
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
	texture->Bind();

	glm::mat4 mvp = glm::ortho(0.0f, 960.0f, 0.0f, 720.0f, -1.0f, 1.0f) * 
					glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0)) * 
					glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

	shader->Bind();
	shader->SetMatrix4x4("mvp", mvp);

	renderer->Draw(vao, ibo, shader);
}

void Nuwa::GameWindow::OnFrameBufferSizeChanged(GLFWwindow* window, int width, int height)
{
	GL_ASSERT(glViewport(0, 0, width, height));
}
