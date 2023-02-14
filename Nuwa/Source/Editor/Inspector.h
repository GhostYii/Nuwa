#pragma once
#include "EditorGUI.h"

namespace Nuwa
{
	namespace Editor
	{
		class Inspector : public EditorGUI
		{
		public:
			Inspector();
			~Inspector() = default;


			virtual void OnGUI() override;
		};
	}
}