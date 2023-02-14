#include "EditorGUI.h"

namespace Nuwa
{
	namespace Editor
	{
		EditorGUI::EditorGUI()
			: id(UUID::Generate()), title("EditorGUI"), isOpen(true)
		{
			
		}

		EditorGUI::~EditorGUI()
		{
		}

		void EditorGUI::RenderGUI()
		{
			ImGui::Begin(title.c_str(), &isOpen);
			OnGUI();
			ImGui::End();
		}
	}
}

