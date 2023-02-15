#include "Editor.h"
#include "Inspector.h"
#include "../GameScene.h"
#include "../Component/BehaviorComponent.h"
#include<glm/gtc/type_ptr.hpp>

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
				ImGui::DragFloat3("Position", glm::value_ptr(currentGameObject->transform.position), 0.1f);

				auto euler = glm::eulerAngles(currentGameObject->transform.rotation);
				euler.x = glm::degrees(euler.x);
				euler.y = glm::degrees(euler.y);
				euler.z = glm::degrees(euler.z);
				ImGui::DragFloat3("Rotation", glm::value_ptr(euler));
				currentGameObject->transform.rotation = Quaternion(glm::radians(euler));

				ImGui::DragFloat3("Scale", glm::value_ptr(currentGameObject->transform.scale), 0.1f);
				ImGui::Unindent();
			}

			for (auto iter : currentGameObject->components)
			{
				if (dynamic_cast<BehaviorComponent*>(iter.second))
				{
					auto comp = dynamic_cast<BehaviorComponent*>(iter.second);
					std::string name = typeid(*comp).name();
					name.erase(name.begin(), name.begin() + 6);
					if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
					{
						comp->InternalOnInspectorGUI();
					}
				}
			}
		}
	}
}