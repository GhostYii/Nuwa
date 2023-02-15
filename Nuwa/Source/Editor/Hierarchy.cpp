#include "Hierarchy.h"
#include "../GameScene.h"

namespace Nuwa
{
	namespace Editor
	{
		Hierarchy::Hierarchy()
			: currentScene(nullptr), currentSelectionID(0), isSceneTreeOpen(true)
		{
			title = "Hierarchy";
		}

		void Hierarchy::OnGUI()
		{
			if (!currentScene)
			{
				ImGui::Text("No Scene Detected.");
				return;
			}
								
			if (ImGui::TreeNodeEx(currentScene->name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				for (auto obj : currentScene->GetAllGameObjects())
				{
					//if (!selection.count(obj->GetInstanceID()))
					//	selection[obj->GetInstanceID()] = false;
					if (ImGui::Selectable(obj->name.c_str(), currentSelectionID == obj->GetInstanceID()))
					{
						//if (!ImGui::GetIO().KeyCtrl)    // Clear selection when CTRL is not held
						//	memset(selection, 0, sizeof(selection));
						//selection[obj->GetInstanceID()] = !selection[obj->GetInstanceID()];

						currentSelectionID = obj->GetInstanceID();
					}
				}
				ImGui::TreePop();
			}
		}

		void Hierarchy::SetCurrentScene(Nuwa::GameScene* scene)
		{
			currentScene = scene;
		}
	}
}