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
			if (isOpen)
			{
				if (!ImGui::Begin(title.c_str(), &isOpen, ImGuiWindowFlags_NoCollapse))
				{
					ImGui::End();
				}
				else
				{
					OnGUI();
					ImGui::End();
				}
			}
		}
	}
}

