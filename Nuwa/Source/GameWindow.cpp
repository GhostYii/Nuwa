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
			camera->transform.position.z = 10.0f;

			Camera* cam = new Camera();
			camera->AddComponent(cam);			

			// create test game object
			GameObject* testGO = new GameObject("test game object");

			std::vector<MeshVertex> vertices =
			{
				{ { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
				{ {  1.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
				{ {  1.0f,  1.0f, 0.0f }, { 1.0f, 1.0f } },
				{ { -1.0f,  1.0f, 0.0f }, { 0.0f, 1.0f } }
			};

			std::vector<uint> indices =
			{
				0, 1, 2,
				2, 3, 0
			};

			Mesh* mesh = new Mesh();
			mesh->SetMeshVertices(vertices, indices);

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

		auto obj = scene->Find("camera")->GetComponent<Camera>();
		ImGui::DragInt("fov", &obj->fieldOfView);


		//ImGui::Begin(camera->name.c_str());
		//ImGui::DragFloat3("Position##cam", glm::value_ptr(camera->transform.position));
		//auto camEuler = glm::eulerAngles(camera->transform.rotation);
		//camEuler.x = glm::degrees(camEuler.x);
		//camEuler.y = glm::degrees(camEuler.y);
		//camEuler.z = glm::degrees(camEuler.z);
		//ImGui::DragFloat3("Rotation##cam", glm::value_ptr(camEuler));
		//camera->transform.rotation = Quaternion(glm::radians(camEuler));

		//ImGui::ShowDemoWindow();


		//if (ImGui::CollapsingHeader("Projection##projection1"))
		//{
		//	Camera* cam = camera->GetComponent<Camera>();
		//	int val = cam->orthographic ? 1 : 0;
		//	const char* items[] = { "Perspective", "Orthographic" };
		//	ImGui::Combo("Projection##projection2", &val, items, 2);
		//	cam->orthographic = val;

		//	if (!cam->orthographic)
		//	{
		//		ImGui::DragInt("FOV", &cam->fieldOfView, 1, 1, 179);
		//	}
		//	else
		//	{
		//		ImGui::DragFloat("Size", &cam->orthoSize, 0.1f);
		//	}

		//	float zNear = cam->GetNearClipPlane();
		//	float zFar = cam->GetFarClipPlane();

		//	ImGui::Text("Clipping Planes");
		//	ImGui::Indent();
		//	ImGui::DragFloat("Near", &zNear);
		//	ImGui::DragFloat("Far", &zFar);
		//	ImGui::Unindent();

		//	cam->SetClipPlane(zNear, zFar);
		//}


		//ImGui::End();

		//ImGui::Begin(testGO->name.c_str());
		//ImGui::DragFloat3("Position##go", glm::value_ptr(testGO->transform.position));
		//auto euler = glm::eulerAngles(testGO->transform.rotation);
		//euler.x = glm::degrees(euler.x);
		//euler.y = glm::degrees(euler.y);
		//euler.z = glm::degrees(euler.z);
		//ImGui::DragFloat3("Rotation##go", glm::value_ptr(euler));

		//testGO->transform.rotation = Quaternion(glm::radians(euler));

		//ImGui::DragFloat3("Scale", glm::value_ptr(testGO->transform.scale));
		//ImGui::End();
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