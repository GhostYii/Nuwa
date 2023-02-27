#ifdef NUWA_EDITOR

#include "Editor.h"
#include "Hierarchy.h"
#include "../GameScene.h"

namespace Nuwa
{
	namespace Editor
	{
		Hierarchy::Hierarchy()
			: isSceneTreeOpen(true)
		{
			title = "Hierarchy";
		}

		void Hierarchy::OnGUI()
		{
			if (!EditorMode::currentScene)
			{
				ImGui::Text("No Scene Detected.");
				return;
			}
								
			if (ImGui::TreeNodeEx(EditorMode::currentScene->name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				for (auto obj : EditorMode::currentScene->GetAllGameObjects())
				{
					//if (!selection.count(obj->GetInstanceID()))
					//	selection[obj->GetInstanceID()] = false;
					if (ImGui::Selectable((obj->name + "##" + std::to_string(obj->GetInstanceID())).c_str(), EditorMode::currentSelectionID == obj->GetInstanceID()))
					{
						//if (!ImGui::GetIO().KeyCtrl)    // Clear selection when CTRL is not held
						//	memset(selection, 0, sizeof(selection));
						//selection[obj->GetInstanceID()] = !selection[obj->GetInstanceID()];

						EditorMode::currentSelectionID = obj->GetInstanceID();
					}
				}
				ImGui::TreePop();
			}
		}
	}
}

#endif // NUWA_EDITOR