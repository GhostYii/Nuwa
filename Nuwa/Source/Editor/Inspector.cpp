#include "Inspector.h"

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
			ImGui::Text("this is a text in inspector tab.");
		}
	}
}