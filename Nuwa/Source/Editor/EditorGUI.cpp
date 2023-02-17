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

		void EditorGUI::DrawDragFloat(std::string name, float& value)
		{
			ImGui::PushID(name.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, EDITOR_DEFAULT_TITLE_WIDTH);
			ImGui::Text(name.c_str());
			ImGui::NextColumn();

			ImGui::DragFloat(("##" + name).c_str(), &value, 0.1f);

			ImGui::Columns();
			ImGui::PopID();
		}

		void EditorGUI::DrawSlideInt(std::string name, int& value, int min, int max)
		{
			ImGui::PushID(name.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, EDITOR_DEFAULT_TITLE_WIDTH);
			ImGui::Text(name.c_str());
			ImGui::NextColumn();

			ImGui::SliderInt(("##" + name).c_str(), &value, min, max);

			ImGui::Columns();
			ImGui::PopID();
		}

		void EditorGUI::DrawDragVector3(std::string name, Vector3& value)
		{
			ImGui::PushID(name.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, EDITOR_DEFAULT_TITLE_WIDTH);
			ImGui::AlignTextToFramePadding();
			ImGui::Text(name.c_str());
			ImGui::NextColumn();

			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

			ImGui::AlignTextToFramePadding();
			ImGui::Text("X");
			ImGui::SameLine();
			ImGui::DragFloat("##X", &value.x, 0.1f);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::Text("Y");
			ImGui::SameLine();
			ImGui::DragFloat("##Y", &value.y, 0.1f);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::Text("Z");
			ImGui::SameLine();
			ImGui::DragFloat("##Z", &value.z, 0.1f);
			ImGui::PopItemWidth();

			ImGui::Columns();
			ImGui::PopID();

		}

		void EditorGUI::DrawLabel(std::string name, std::string value)
		{
			ImGui::PushID(name.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, EDITOR_DEFAULT_TITLE_WIDTH);
			ImGui::Text(name.c_str());
			ImGui::NextColumn();

			ImGui::Text(value.c_str());

			ImGui::Columns();
			ImGui::PopID();
		}

		void EditorGUI::DrawInputText(std::string name, char* buf, size_t bufSize)
		{
			ImGui::PushID(name.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, EDITOR_DEFAULT_TITLE_WIDTH);
			ImGui::Text(name.c_str());
			ImGui::NextColumn();

			ImGui::InputText(("##" + name).c_str(), buf, bufSize);

			ImGui::Columns();
			ImGui::PopID();
		}

		void EditorGUI::DrawCombo(std::string name, int* currentItem, const char* const items[], int itemsCount)
		{
			ImGui::PushID(name.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, EDITOR_DEFAULT_TITLE_WIDTH);
			ImGui::Text(name.c_str());
			ImGui::NextColumn();

			ImGui::Combo(("##" + name).c_str(), currentItem, items, itemsCount);

			ImGui::Columns();
			ImGui::PopID();
		}
	}
}

