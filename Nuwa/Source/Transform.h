#pragma once
#include "EngineTypes.h"

namespace Nuwa
{
	class Transform
	{
	public:
		Transform();
		~Transform() = default;

		Vector3 position;

		//float pitch, yaw, roll;
		Vector3 eulerAngles;
		mutable Quaternion rotation;
		Vector3 scale;

		//Vector3 localPosition;
		//Vector3 localRotation;
		//Vector3 localScale;

		Vector3 Front();
		Vector3 Right();
		Vector3 Up();

		// ¡–æÿ’Û¥Ê¥¢–Œ Ω
		// [RT.x][UP.x][BK.x][POS.x]
		// [RT.y][UP.y][BK.y][POS.y]
		// [RT.z][UP.z][BK.z][POS.Z]
		// [ 0  ][ 0  ][  0 ][  US ]

		Matrix4x4 GetModelMatrix() const;
	};
}
