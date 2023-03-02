#ifdef NUWA_EDITOR

#include "GameView.h"
#include "Editor.h"
#include "../GameScene.h"
#include "../Component/Camera.h"
#include "../Global.h"
#include "glm/gtc/type_ptr.hpp"
#include "../Input/Input.h"

namespace Nuwa
{
	namespace Editor
	{
		GameView::GameView()
		{
			title = "Game View";
		}

		GameView::~GameView()
		{
		}

		void GameView::OnGizmos()
		{
			if (!EditorMode::currentScene || !GameScene::mainCamera)
				return;

			ImGuizmo::SetRect(Global::WindowPosition.x, Global::WindowPosition.y, Global::Resolution.x, Global::Resolution.y);
			ImGuizmo::SetOrthographic(GameScene::mainCamera->orthographic);
			ImGuizmo::DrawGrid
			(
				glm::value_ptr(GameScene::mainCamera->GetViewMatrix()),
				glm::value_ptr(GameScene::mainCamera->GetProjectMatrix()),
				glm::value_ptr(Matrix4x4(1.0f)),
				GameScene::mainCamera->GetFarClipPlane()
			);

			GameObject* currentGameObject = EditorMode::currentScene->Find(EditorMode::currentSelectionID);

			if (!currentGameObject)
				return;

			if (Input::GetKeyDown(KeyCode::W))
				EditorMode::currentGizmosOperation = ImGuizmo::TRANSLATE;
			else if (Input::GetKeyDown(KeyCode::E))
				EditorMode::currentGizmosOperation = ImGuizmo::ROTATE;
			else if (Input::GetKeyDown(KeyCode::R))
				EditorMode::currentGizmosOperation = ImGuizmo::SCALE;

			Matrix4x4 objMatrix = currentGameObject->transform.GetModelMatrix();
			ImGuizmo::Manipulate
			(
				glm::value_ptr(GameScene::mainCamera->GetViewMatrix()),
				glm::value_ptr(GameScene::mainCamera->GetProjectMatrix()),
				EditorMode::currentGizmosOperation,
				ImGuizmo::WORLD,
				glm::value_ptr(objMatrix),
				NULL,
				NULL
			);
			ImGuizmo::DecomposeMatrixToComponents
			(
				glm::value_ptr(objMatrix),
				glm::value_ptr(currentGameObject->transform.position),
				glm::value_ptr(currentGameObject->transform.eulerAngles),
				glm::value_ptr(currentGameObject->transform.scale)
			);


		}
	}
}

#endif // NUWA_EDITOR