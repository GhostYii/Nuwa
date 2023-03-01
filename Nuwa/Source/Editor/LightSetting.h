#pragma once
#ifdef NUWA_EDITOR

#include "EditorGUI.h"

namespace Nuwa
{
	namespace Editor
	{
		class LightSetting : public EditorGUI
		{
		public:
			LightSetting();
			~LightSetting() = default;

			virtual void OnGUI() override;		
		};
	}
}

#endif // NUWA_EDITOR