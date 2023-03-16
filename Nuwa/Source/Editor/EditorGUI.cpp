#ifdef NUWA_EDITOR

#include "Editor.h"
#include "EditorGUI.h"
#include "glm/gtc/type_ptr.hpp"
#include "../GameScene.h"

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
			switch (EditorMode::currentDrawMode)
			{
				case 0: GL_ASSERT(glPolygonMode(GL_FRONT_AND_BACK, GL_POINT)); break;
				case 1: GL_ASSERT(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)); break;
				case 2: GL_ASSERT(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)); break;
				default:GL_ASSERT(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)); break;
			}

			if (isOpen)
			{
				if (!ImGui::Begin(title.c_str(), &isOpen, ImGuiWindowFlags_NoCollapse))
				{
					ImGui::End();
				}
				else
				{
					ImGui::AlignTextToFramePadding();
					OnGUI();
					ImGui::End();
				}
			}

			if (EditorMode::isShowGizmos)
				OnGizmos();
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

		void EditorGUI::DrawSlideFloat(std::string name, float& value, float min, float max)
		{
			ImGui::PushID(name.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, EDITOR_DEFAULT_TITLE_WIDTH);
			ImGui::Text(name.c_str());
			ImGui::NextColumn();

			ImGui::AlignTextToFramePadding();
			ImGui::SliderFloat(("##" + name).c_str(), &value, min, max);
			ImGui::Columns();
			ImGui::PopID();

			ImGui::SameLine();
			ImGui::SetNextItemWidth(EDITOR_DEFAULT_DRAG_WIDTH);
			ImGui::DragFloat(("##" + name).c_str(), &value, 0.1f, min, max, "%.2f");
		}

		void EditorGUI::DrawDragInt(std::string name, int& value)
		{
			ImGui::PushID(name.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, EDITOR_DEFAULT_TITLE_WIDTH);
			ImGui::Text(name.c_str());
			ImGui::NextColumn();

			ImGui::DragInt(("##" + name).c_str(), &value);

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

			ImGui::SameLine();
			ImGui::SetNextItemWidth(EDITOR_DEFAULT_DRAG_WIDTH);
			ImGui::DragInt(("##" + name).c_str(), &value, 1.0f, min, max);
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

		void EditorGUI::DrawSingleText(const char* fmt, ...)
		{
			va_list args;
			va_start(args, fmt);
			ImGui::Text(fmt, args);
			va_end(args);
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

		void EditorGUI::DrawEditColor3(std::string name, Vector3& color)
		{
			ImGui::PushID(name.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, EDITOR_DEFAULT_TITLE_WIDTH);
			ImGui::Text(name.c_str());
			ImGui::NextColumn();

			ImGui::ColorEdit3(("##" + name).c_str(), glm::value_ptr(color));

			ImGui::Columns();
			ImGui::PopID();
		}

		void EditorGUI::DrawPickColor3(std::string name, Vector3& color)
		{
			ImGui::PushID(name.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, EDITOR_DEFAULT_TITLE_WIDTH);
			ImGui::Text(name.c_str());
			ImGui::NextColumn();

			ImGui::ColorPicker3(("##" + name).c_str(), glm::value_ptr(color));

			ImGui::Columns();
			ImGui::PopID();
		}

		void EditorGUI::DrawToggle(std::string name, bool& isOn)
		{
			ImGui::PushID(name.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, EDITOR_DEFAULT_TITLE_WIDTH);
			ImGui::Text(name.c_str());
			ImGui::NextColumn();

			ImGui::Checkbox(("##" + name).c_str(), &isOn);

			ImGui::Columns();
			ImGui::PopID();
		}
	}
}

#endif // NUWA_EDITOR