#ifdef NUWA_EDITOR

#include "Editor.h"
#include "../GameScene.h"
#include "../Component/BehaviorComponent.h"
#include "../Input/Input.h"

namespace Nuwa
{
	namespace Editor
	{
		Nuwa::GameScene* EditorMode::currentScene = nullptr;
		uint64 EditorMode::currentSelectionID = 0;
		ImGuizmo::OPERATION EditorMode::currentGizmosOperation = ImGuizmo::TRANSLATE;
		bool EditorMode::isShowGizmos = true;
		int EditorMode::currentDrawMode = 2;

		EditorMode::EditorMode()
		{
			spdlog::info("Editor Mode On.");
		}

		EditorMode::~EditorMode()
		{
			for (auto iter : editorGUIs)
			{
				iter->Destory();
			}
		}

		void EditorMode::AddEditorGUI(EditorGUI* editorGUI, bool isOpen)
		{
			if (!editorGUI)
				return;

			// 编辑器性能优化？
			if (std::find(editorGUIs.begin(), editorGUIs.end(), editorGUI) != editorGUIs.end())
				return;

			editorGUI->Start();
			editorGUI->isOpen = isOpen;
			editorGUIs.push_back(editorGUI);

		}

		void EditorMode::OnEditorGUI()
		{
			if (Input::GetKeyDown(KeyCode::H))
			{
				for (auto iter : editorGUIs) if (iter->title == "Hierarchy")
				{
					iter->isOpen = !iter->isOpen;
					break;
				}
			}
			else if (Input::GetKeyDown(KeyCode::I))
			{
				for (auto iter : editorGUIs) if (iter->title == "Inspector")
				{
					iter->isOpen = !iter->isOpen;
					break;
				}
			}
			else if (Input::GetKeyDown(KeyCode::C))
			{
				static bool isOpen = false;
				for (auto iter : editorGUIs)
					iter->isOpen = isOpen;
				isOpen = !isOpen;
			}
			else if (Input::GetKeyDown(KeyCode::L))
			{
				for (auto iter : editorGUIs) if (iter->title == "Light Setting")
				{
					iter->isOpen = !iter->isOpen;
					break;
				}
			}
			else if (Input::GetKeyDown(KeyCode::V))
			{
				for (auto iter : editorGUIs) if (iter->title == "Game View")
				{
					iter->isOpen = !iter->isOpen;
					break;
				}
			}

			for (auto iter : editorGUIs)
				iter->RenderGUI();

		}

		void EditorMode::SetCurrentScene(Nuwa::GameScene* scene)
		{
			EditorMode::currentScene = scene;
		}
	}
}

#endif // NUWA_EDITOR