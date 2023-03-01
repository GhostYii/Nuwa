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

		void EditorMode::AddEditorGUI(EditorGUI* editorGUI)
		{
			if (!editorGUI)
				return;

			// �༭�������Ż���
			if (std::find(editorGUIs.begin(), editorGUIs.end(), editorGUI) != editorGUIs.end())
				return;

			editorGUI->Start();
			editorGUIs.push_back(editorGUI);
		}

		void EditorMode::OnEditorGUI()
		{
			if (Input::GetKeyDown(KeyCode::H))
			{
				for (auto iter : editorGUIs)
					if (iter->title == "Hierarchy")
						iter->isOpen = !iter->isOpen;
			}
			else if (Input::GetKeyDown(KeyCode::I))
			{
				for (auto iter : editorGUIs)
					if (iter->title == "Inspector")
						iter->isOpen = !iter->isOpen;
			}
			else if (Input::GetKeyDown(KeyCode::C))
			{
				static bool isOpen = false;
				for (auto iter : editorGUIs)
					iter->isOpen = isOpen;
				isOpen = !isOpen;
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