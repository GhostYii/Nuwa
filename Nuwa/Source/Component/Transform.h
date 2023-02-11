#pragma once
#include "Component.h"

namespace Nuwa
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform() = default;

		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
		
		Vector3 eulerAngles;

		//Vector3 localPosition;
		//Vector3 localRotation;
		//Vector3 localScale;

		//Vector3 Front();
		//Vector3 Right();
		//Vector3 Up();
	};
}
