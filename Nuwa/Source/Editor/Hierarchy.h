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

			void SetCurrentScene(Nuwa::GameScene* scene);

		private:
			Nuwa::GameScene* currentScene;

			//std::unordered_map<uint64, bool> selection;
			uint64 currentSelectionID;

			bool isSceneTreeOpen;
		};
	}
}