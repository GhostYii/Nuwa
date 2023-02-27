#ifdef NUWA_EDITOR

#include "Editor.h"
#include "../GameScene.h"
#include "../Component/BehaviorComponent.h"

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

			// 编辑器性能优化？
			if (std::find(editorGUIs.begin(), editorGUIs.end(), editorGUI) != editorGUIs.end())
				return;

			editorGUI->Start();
			editorGUIs.push_back(editorGUI);
		}

		void EditorMode::OnEditorGUI()
		{
			if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_H))
			{
				for (auto iter : editorGUIs)
					if (iter->title == "Hierarchy")
						iter->isOpen = !iter->isOpen;
			}
			else if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_I))
			{
				for (auto iter : editorGUIs)
					if (iter->title == "Inspector")
						iter->isOpen = !iter->isOpen;
			}
			else if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_C))
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