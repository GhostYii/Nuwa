#pragma once
#include "EngineTypes.h"

namespace Nuwa
{
	class Global
	{
	private:
		Global() = default;
		~Global() = default;

	public:
		static Vector2Int Resolution;
		static bool IsFullScreen;

		static bool IsEditor;

		static Vector3 AmbientColor;
		static Vector3 DiffuseColor;
		static Vector3 SpecularColor;
	};
}
