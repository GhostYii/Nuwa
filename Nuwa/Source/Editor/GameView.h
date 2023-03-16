#pragma once
#ifdef NUWA_EDITOR

#include "EditorGUI.h"

namespace Nuwa
{
	namespace Editor
	{
		class GameView : public EditorGUI
		{
		public:
			GameView();
			virtual ~GameView();
			 
		protected:
			virtual void OnGizmos() override;
			virtual void OnGUI() override;
		};
	}
}

#endif // NUWA_EDITOR