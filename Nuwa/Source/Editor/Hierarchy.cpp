#include "Hierarchy.h"

namespace Nuwa
{
	namespace Editor
	{
		Hierarchy::Hierarchy()
		{
			title = "Hierarchy";
		}

		void Hierarchy::OnGUI()
		{
			ImGui::Text("this is a text in hierarchy tab.");
		}
	}
}