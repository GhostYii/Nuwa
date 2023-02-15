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
			for (auto iter : editorGUIs)
				iter->RenderGUI();			
		}

		void EditorMode::SetCurrentScene(Nuwa::GameScene* scene)
		{
			EditorMode::currentScene = scene;
		}
	}
}