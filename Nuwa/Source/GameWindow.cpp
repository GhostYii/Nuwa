#include "GameWindow.h"
#include "imgui/imgui.h"
#include "spdlog/spdlog.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Global.h"
#include "EngineMacros.h"
#include "Input/InputSystem.h"

#include "Mesh.h"
#include "Component/MeshRenderer.h"
#include "Component/Light.h"
#include "Component/SpriteRenderer.h"
#include "Component/CameraView.h"


namespace Nuwa
{
	GameWindow::GameWindow(const WindowConfig& config)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->config = config;
		GLFWmonitor* monitor = config.isFullScreen ? glfwGetPrimaryMonitor() : nullptr;
		window = glfwCreateWindow(config.width, config.height, config.title.c_str(), monitor, nullptr);

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
		GL_ASSERT(glEnable(GL_CULL_FACE));

		// init input system
		InputSystem::CreateInstance();
		InputSystem::GetInstance()->Init(*this);
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
			editor->AddEditorGUI(new Editor::LightSetting());
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

			CameraView* cv = new CameraView(cam);
			camera->AddComponent(cv);

			//// create test game object
			//GameObject* test = new GameObject("game object");
			////test->transform.rotation = Quaternion(glm::radians(Vector3(-90, 45, 0)));

			//Mesh* mesh = new Mesh();
			////mesh->LoadFromObj("Resources/Geometry/cube.obj");
			//mesh->LoadFromObj("Resources/Models/Lowpoly_tree_sample.obj");


			//MeshRenderer* mr = new MeshRenderer();
			//mr->SetMesh(mesh, "Resources/Shaders/Default.shader");
			////mr->SetCamera(cam);
			//test->AddComponent(mr);


			GameObject* test2 = new GameObject("game object");

			Mesh* mesh2 = new Mesh();
			mesh2->LoadFromObj("Resources/Models/wall_block.obj");


			MeshRenderer* mr2 = new MeshRenderer();
			mr2->SetMesh(mesh2, "Resources/Shaders/Default.vert", "Resources/Shaders/Default.frag");
			//mr2->SetCamera(cam);
			test2->AddComponent(mr2);

			// create light gameobject
			GameObject* light = new GameObject("direction light");

			auto lightComp = new Light();
			lightComp->SetGameScene(scene);
			light->AddComponent(lightComp);

			// create light gameobject
			GameObject* light2 = new GameObject("point light");

			auto pointLight = new Light();
			pointLight->type = LightType::Point;
			pointLight->SetGameScene(scene);
			light2->AddComponent(pointLight);

#ifdef NUWA_EDITOR

#endif // NUWA_EDITOR

			scene->AddGameObject(camera);
			scene->AddGameObject(light);
			scene->AddGameObject(light2);
			//scene->AddGameObject(test);
			scene->AddGameObject(test2);
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
		InputSystem::GetInstance()->Update(*this);
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
		Global::Resolution.x = width;
		Global::Resolution.y = height;
		GL_ASSERT(glViewport(0, 0, width, height));

		//spdlog::info("aspect: {}", GetScreenAspect());
	}
}