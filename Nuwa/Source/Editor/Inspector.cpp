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
			if (!currentGameObject)
				return;



		}

		void Inspector::SetGameObject(GameObject* obj)
		{
			currentGameObject = obj;
		}
	}
}