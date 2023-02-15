#pragma once
#include "EditorGUI.h"

namespace Nuwa
{
	class GameScene;
	namespace Editor
	{
		class Hierarchy : public EditorGUI
		{
		public:
			Hierarchy();
			~Hierarchy() = default;

			virtual void OnGUI() override;

		private:
			bool isSceneTreeOpen;
		};
	}
}