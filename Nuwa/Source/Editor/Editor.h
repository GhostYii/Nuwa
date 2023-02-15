#pragma once
#include "../EngineTypes.h"
#include "../EngineMacros.h"
#include "../Basic/UUID.h"

#include "EditorGUI.h"

namespace Nuwa
{
	class GameScene;
	namespace Editor
	{
		//class Hierarchy;
		//class Inspector;

		class EditorMode
		{
		public:
			EditorMode();
			~EditorMode();

			void AddEditorGUI(EditorGUI* editorGUI);

			void OnEditorGUI();

			//// bad idea
			//void RegisterHierarchy(Hierarchy* panel);
			//void RegisterInspector(Inspector* panel);

			static uint64 currentSelectionID;
			static GameScene* currentScene;
			static void SetCurrentScene(Nuwa::GameScene* scene);

		private:
			std::vector<EditorGUI*> editorGUIs;
		};
	}
}