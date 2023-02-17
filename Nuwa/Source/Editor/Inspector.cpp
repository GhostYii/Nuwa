#include "Editor.h"
#include "Inspector.h"
#include "../GameScene.h"
#include "../Component/BehaviorComponent.h"
#include<glm/gtc/type_ptr.hpp>

#include "../Transform.h"
#include "../Component/Camera.h"

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
			DrawTransform(currentGameObject->transform);

			for (auto& iter : currentGameObject->components)
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

		void Inspector::DrawTransform(Transform& transform)
		{
			if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Indent();

				EditorGUI::DrawDragVector3("Position", transform.position);
				
				auto euler = glm::eulerAngles(transform.rotation);
				euler.x = glm::degrees(euler.x);
				euler.y = glm::degrees(euler.y);
				euler.z = glm::degrees(euler.z);
				EditorGUI::DrawDragVector3("Rotation", euler);
				// TODO: -0.0 && abs>360
				transform.rotation = Quaternion(glm::radians(euler));

				EditorGUI::DrawDragVector3("Scale", transform.scale);

				ImGui::Unindent();				
			}
		}
	}
}