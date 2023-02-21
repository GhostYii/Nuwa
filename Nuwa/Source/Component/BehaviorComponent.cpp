#include "BehaviorComponent.h"
#include "imgui/imgui.h"
#include "../GameObject.h"

namespace Nuwa
{
	void BehaviorComponent::InternalUpdate()
	{
		if (!gameObject->IsActive())
			return;

		if (enable)
			Update();

		if (prevEnable != enable)
		{
			if (enable)	OnEnable();
			else OnDisable();
		}
	}

	void BehaviorComponent::InternalLateUpdate()
	{
		if (!gameObject->IsActive())
			return;

		if (enable)
			LateUpdate();

		prevEnable = enable;
	}

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

