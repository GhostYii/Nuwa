#include "BehaviorComponent.h"
#include "imgui/imgui.h"

namespace Nuwa
{
	void BehaviorComponent::InternalOnInspectorGUI()
	{
		// ����Ⱦ�����GUI
		if (typeid(this) == typeid(BehaviorComponent*))
			return;

		if (ImGui::CollapsingHeader(typeid(this).name(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Indent();
			OnInspectorGUI();
			ImGui::Unindent();
		}
	}

}

