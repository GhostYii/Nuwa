#include "BehaviorComponent.h"
#include "imgui/imgui.h"

namespace Nuwa
{
	void BehaviorComponent::InternalOnInspectorGUI()
	{
		ImGui::Indent();
		ImGui::Text("memery address: %llu", this);
		OnInspectorGUI();
		ImGui::Unindent();
	}

}

