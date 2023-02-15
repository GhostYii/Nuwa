#pragma once
#include "EditorGUI.h"

namespace Nuwa
{
	class GameObject;
	namespace Editor
	{
		class Inspector : public EditorGUI
		{
		public:
			Inspector();
			~Inspector() = default;

			virtual void OnGUI() override;

			void SetGameObject(GameObject* obj);

		private:
			GameObject* currentGameObject;
		};
	}
}