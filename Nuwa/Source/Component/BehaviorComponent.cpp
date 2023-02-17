#include "BehaviorComponent.h"
#include "imgui/imgui.h"

namespace Nuwa
{
	void BehaviorComponent::InternalOnInspectorGUI()
	{
		ImGui::Indent();
		//ImGui::Text("memery address: %llu", this);
		ImGui::Checkbox("Enable", &enable);
		if (!enable)
		{
			ImGui::Unindent();
			return;
		}
		OnInspectorGUI();
		ImGui::Unindent();
	}

}

