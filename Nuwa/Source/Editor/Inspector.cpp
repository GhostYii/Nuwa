#include "Editor.h"
#include "Inspector.h"
#include "../GameScene.h"
#include "../Component/BehaviorComponent.h"

namespace Nuwa
{
	namespace Editor
	{
		Inspector::Inspector()
		{
			title = "Inspector";
		}

		void Inspector::OnGUI()
		{
			if (!EditorMode::currentScene)
				return;

			currentGameObject = EditorMode::currentScene->Find(EditorMode::currentSelectionID);

			if (!currentGameObject)
				return;

			ImGui::Text("Properties(%s)", currentGameObject->name.c_str());
			if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Indent();
				ImGui::Text("transform gui here");
				ImGui::Unindent();
			}

			for (const auto iter : currentGameObject->components)
			{
				if (dynamic_cast<BehaviorComponent*>(iter.second))
				{
					const auto comp = dynamic_cast<BehaviorComponent*>(iter.second);
					if (ImGui::CollapsingHeader(typeid(*comp).name(), ImGuiTreeNodeFlags_DefaultOpen))
					{
						comp->InternalOnInspectorGUI();
					}
				}
			}


		}
	}
}