#include "Editor.h"
#include "Inspector.h"
#include "../GameScene.h"

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
			if (!EditorMode::currentScene)
				return;

			currentGameObject = EditorMode::currentScene->Find(EditorMode::currentSelectionID);

			if (!currentGameObject)
				return;




		}

		void Inspector::SetGameObject(GameObject* obj)
		{
			currentGameObject = obj;
		}
	}
}