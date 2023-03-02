#ifdef NUWA_EDITOR

#include "Editor.h"
#include "Inspector.h"
#include "../GameScene.h"
#include "../Component/Component.h"
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

			ImGui::Checkbox("##active", &currentGameObject->isActive);
			ImGui::SameLine();
			ImGui::Text("Properties(%s)", currentGameObject->name.c_str());

			DrawTransform(currentGameObject->transform);

			for (auto& iter : currentGameObject->components)
			{
				//auto comp = dynamic_cast<Component*>(iter.second);
				std::string name = typeid(*iter.second).name();
				name.erase(name.begin(), name.begin() + 6);
				if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
				{
					iter.second->InternalOnInspectorGUI();
				}
			}
		}

		void Inspector::DrawTransform(Transform& transform)
		{
			if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Indent();

				EditorGUI::DrawDragVector3("Position", transform.position);
				EditorGUI::DrawDragVector3("Rotation", transform.eulerAngles);
				// TODO: abs>360
				//if (std::fabs(transform.eulerAngles.x) > 360.0f)
				//	transform.eulerAngles.x -= (transform.eulerAngles.x / 360.0f) * 360.0f;
				//if (std::fabs(transform.eulerAngles.y) > 360.0f)
				//	transform.eulerAngles.y -= (transform.eulerAngles.y / 360.0f)  * 360.0f;
				//if (std::fabs(transform.eulerAngles.z) > 360.0f)
				//	transform.eulerAngles.z -= (transform.eulerAngles.z / 360.0f) * 360.0f;
				transform.rotation = Quaternion(glm::radians(transform.eulerAngles));
				EditorGUI::DrawDragVector3("Scale", transform.scale);

				ImGui::Unindent();
			}
		}
	}
}

#endif // NUWA_EDITOR