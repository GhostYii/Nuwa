#pragma once
#ifdef NUWA_EDITOR

#include "EditorGUI.h"

namespace Nuwa
{
	class GameObject;
	class Transform;
	namespace Editor
	{
		class Inspector : public EditorGUI
		{
		public:
			Inspector();
			~Inspector() = default;

			virtual void OnGUI() override;

		private:
			GameObject* currentGameObject;

			void DrawTransform(Transform& transform);			
		};
	}
}

#endif // NUWA_EDITOR