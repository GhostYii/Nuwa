#include "GameWindow.h"
#include "imgui/imgui.h"
#include "spdlog/spdlog.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "EngineMacros.h"

#include "Mesh.h"
#include "Component/MeshRenderer.h"
//#include "Component/Camera.h"

namespace Nuwa
{

	GameWindow::GameWindow(const WindowConfig& config)
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

		GL_ASSERT(glEnable(GL_DEPTH_TEST));
	}

	void GameWindow::OnStart()
	{
		if (!scene)
		{
			scene = new GameScene("Default Scene");

#ifdef NUWA_EDITOR			
			editor = new Editor::EditorMode();
			EditorMode::SetCurrentScene(scene);

			editor->AddEditorGUI(new Editor::Inspector());
			editor->AddEditorGUI(new Editor::Hierarchy());
#endif // NUWA_EDITOR
		}

		// for test
		if (scene)
		{
			// create camera
			GameObject* camera = new GameObject("camera");
			camera->transform.position.z = 2.0f;

			Camera* cam = new Camera();
			camera->AddComponent(cam);

			// create test game object
			GameObject* testGO = new GameObject("sphere");
			testGO->transform.rotation = Quaternion(glm::radians(Vector3(-90, 45, 0)));

			//std::vector<MeshVertex> vertices =
			//{
			//	{ { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
			//	{ {  1.0f, -1.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
			//	{ {  1.0f,  1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
			//	{ { -1.0f,  1.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } }
			//};

			//std::vector<uint> indices =
			//{
			//	0, 1, 2,
			//	2, 3, 0
			//};

			Mesh* mesh = new Mesh();
			//mesh->SetMeshVertices(vertices, indices);
			mesh->LoadFromObj("Resources/Geometry/sphere.obj");

			MeshRenderer* mr = new MeshRenderer();
			mr->SetMesh(mesh, "Resources/shaders/Default.shader", "Resources/Textures/nuwa.png");
			mr->SetCamera(cam);

			testGO->AddComponent(mr);

			scene->AddGameObject(camera);
			scene->AddGameObject(testGO);
		}
	}

	void GameWindow::OnGUI()
	{
#ifdef NUWA_EDITOR
		if (editor)
			editor->OnEditorGUI();
#endif // NUWA_EDITOR

		//ImGui::ShowDemoWindow();
	}

	void GameWindow::OnUpdate()
	{
		if (scene)
			scene->Update();
	}

	void GameWindow::OnRenderObject()
	{
		if (scene)
			scene->Render();
	}

	void GameWindow::OnFrameBufferSizeChanged(GLFWwindow* window, int width, int height)
	{
		GL_ASSERT(glViewport(0, 0, width, height));
	}
}