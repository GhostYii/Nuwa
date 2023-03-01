#include "LightSetting.h"
#include "../Global.h"

namespace Nuwa
{
	namespace Editor
	{
		LightSetting::LightSetting()
		{
			title = "Light Setting";
		}

		void LightSetting::OnGUI()
		{
			//ImGui::CollapsingHeader("Global Setting")
			DrawEditColor3("Ambient Color", Global::AmbientColor);
			DrawEditColor3("Diffuse Color", Global::DiffuseColor);
			DrawEditColor3("Specular Color", Global::SpecularColor);
		}
	}
}


