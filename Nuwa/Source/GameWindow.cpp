#include "GameWindow.h"
#include "imgui/imgui.h"
#include "spdlog/spdlog.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "EngineMacros.h"

#include "Mesh.h"
#include "Component/MeshRenderer.h"
#include "Component/Camera.h"

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
	// create camera
	camera = new GameObject();
	camera->name = "camera";
	camera->transform.position.z = 10.0f;		

	cam = new Camera();
	
	camera->AddComponent(cam);

	testGO = new GameObject();
	testGO->name = "test game object";

	std::vector<MeshVertex> vertices =
	//{
	//	{ {  0.5f,  0.5f, 0 }, { 1.0f, 1.0f } },  // top right
	//	{ {  0.5f, -0.5f, 0 }, { 1.0f, 0.0f } }, // bottom right
	//	{ { -0.5f, -0.5f, 0 }, { 0.0f, 0.0f } }, // bottom left
	//	{ { -0.5f,  0.5f, 0 }, { 0.0f, 1.0f } }  // top left 
	//};
	{
		{ { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
		{ {  1.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
		{ {  1.0f,  1.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { -1.0f,  1.0f, 0.0f }, { 0.0f, 1.0f } }
	};

	std::vector<uint> indices =
	//{
	//	0, 1, 2,
	//	1, 2, 3
	//};
	{
		0, 1, 2,
		2, 3, 0
	};

	//testGO->AddComponent()
	Mesh* mesh = new Mesh();
	mesh->SetMeshVertices(vertices, indices);

	mr = new MeshRenderer();
	mr->SetMesh(mesh, "Resources/shaders/Default.shader", "Resources/Textures/opengl.png");

	testGO->AddComponent(mr);
}

void Nuwa::GameWindow::OnGUI()
{
	ImGui::Begin(camera->name.c_str());
	ImGui::DragFloat3("Position##cam", glm::value_ptr(camera->transform.position));
	auto camEuler = glm::eulerAngles(camera->transform.rotation);
	camEuler.x = glm::degrees(camEuler.x);
	camEuler.y = glm::degrees(camEuler.y);
	camEuler.z = glm::degrees(camEuler.z);
	ImGui::DragFloat3("Rotation##cam", glm::value_ptr(camEuler));
	camera->transform.rotation = Quaternion(glm::radians(camEuler));
	ImGui::End();

	ImGui::Begin(testGO->name.c_str());
	ImGui::DragFloat3("Position##go", glm::value_ptr(testGO->transform.position));
	auto euler = glm::eulerAngles(testGO->transform.rotation);
	euler.x = glm::degrees(euler.x);
	euler.y = glm::degrees(euler.y);
	euler.z = glm::degrees(euler.z);
	ImGui::DragFloat3("Rotation##go", glm::value_ptr(euler));

	testGO->transform.rotation = Quaternion(glm::radians(euler));

	ImGui::DragFloat3("Scale", glm::value_ptr(testGO->transform.scale));
	ImGui::End();
}

void Nuwa::GameWindow::OnUpdate()
{
}

void Nuwa::GameWindow::OnRenderObject()
{
	if (mr)
		mr->Draw(*cam);

	//auto render = testGO->GetComponent<MeshRenderer>();
	//if (render)
	//{
	//	render->Draw(*camera->GetComponent<Camera>());
	//}
}

void Nuwa::GameWindow::OnFrameBufferSizeChanged(GLFWwindow* window, int width, int height)
{
	GL_ASSERT(glViewport(0, 0, width, height));
}
