#pragma once
#include "../EngineTypes.h"
#include "../EngineMacros.h"
#include "../Basic/UUID.h"

#include "EditorGUI.h"

namespace Nuwa
{
	namespace Editor
	{
		class EditorMode
		{
		public:
			EditorMode();
			~EditorMode();

			void AddEditorGUI(EditorGUI* editorGUI);

			void OnEditorGUI();

		private:
			std::vector<EditorGUI*> editorGUIs;
		};
	}
}