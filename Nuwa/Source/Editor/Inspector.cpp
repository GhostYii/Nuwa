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
			static int id = 0;
			if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Indent();
				// Position
				{
					ImGui::PushID("position");

					ImGui::Columns(2);
					ImGui::AlignTextToFramePadding();
					ImGui::Text("Position");
					ImGui::NextColumn();

					ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

					ImGui::AlignTextToFramePadding();
					ImGui::Text("X");
					ImGui::SameLine();
					ImGui::DragFloat("##X", &transform.position.x, 0.1f);
					ImGui::PopItemWidth();
					ImGui::SameLine();

					ImGui::Text("Y");
					ImGui::SameLine();
					ImGui::DragFloat("##Y", &transform.position.y, 0.1f);
					ImGui::PopItemWidth();
					ImGui::SameLine();

					ImGui::Text("Z");
					ImGui::SameLine();
					ImGui::DragFloat("##Z", &transform.position.z, 0.1f);
					ImGui::PopItemWidth();

					ImGui::Columns();
					ImGui::PopID();
				}
				// Rotation
				{
					auto euler = glm::eulerAngles(transform.rotation);
					euler.x = glm::degrees(euler.x);
					euler.y = glm::degrees(euler.y);
					euler.z = glm::degrees(euler.z);

					ImGui::PushID("rotation");

					ImGui::Columns(2);
					ImGui::AlignTextToFramePadding();
					ImGui::Text("Rotation");
					ImGui::NextColumn();

					ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

					ImGui::AlignTextToFramePadding();
					ImGui::Text("X");
					ImGui::SameLine();
					ImGui::DragFloat("##X", &euler.x, 0.1f);
					ImGui::PopItemWidth();
					ImGui::SameLine();

					ImGui::Text("Y");
					ImGui::SameLine();
					ImGui::DragFloat("##Y", &euler.y, 0.1f);
					ImGui::PopItemWidth();
					ImGui::SameLine();

					ImGui::Text("Z");
					ImGui::SameLine();
					ImGui::DragFloat("##Z", &euler.z, 0.1f);
					ImGui::PopItemWidth();

					ImGui::Columns();
					ImGui::PopID();

					// TODO: -0.0 && abs>360
					transform.rotation = Quaternion(glm::radians(euler));
				}
				// Scale
				{
					ImGui::PushID("scale");

					ImGui::Columns(2);
					ImGui::AlignTextToFramePadding();
					ImGui::Text("Scale");
					ImGui::NextColumn();

					ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

					ImGui::AlignTextToFramePadding();
					ImGui::Text("X");
					ImGui::SameLine();
					ImGui::DragFloat("##X", &transform.scale.x, 0.1f);
					ImGui::PopItemWidth();
					ImGui::SameLine();

					ImGui::Text("Y");
					ImGui::SameLine();
					ImGui::DragFloat("##Y", &transform.scale.y, 0.1f);
					ImGui::PopItemWidth();
					ImGui::SameLine();

					ImGui::Text("Z");
					ImGui::SameLine();
					ImGui::DragFloat("##Z", &transform.scale.z, 0.1f);
					ImGui::PopItemWidth();

					ImGui::Columns();
					ImGui::PopID();
				}

				ImGui::Unindent();
			}
		}
	}
}