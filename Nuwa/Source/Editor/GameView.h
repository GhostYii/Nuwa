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

		private:

		};
	}
}

#endif // NUWA_EDITOR