#pragma once
#include "EditorGUI.h"

namespace Nuwa
{
	namespace Editor
	{
		class Hierarchy : public EditorGUI
		{
		public:
			Hierarchy();
			~Hierarchy() = default;

			virtual void OnGUI() override;
		};
	}
}