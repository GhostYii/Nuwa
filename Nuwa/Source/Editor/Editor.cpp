#include "Editor.h"
namespace Nuwa
{
	namespace Editor
	{
		EditorMode::EditorMode()
		{
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
			for (auto iter : editorGUIs)
				iter->RenderGUI();
		}
	}
}