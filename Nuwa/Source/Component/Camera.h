#pragma once
#include "Component.h"

namespace Nuwa
{
	class Camera : public Component
	{
	public:
		Camera();
		virtual ~Camera() = default;

		// Is the camera orthographic (true) or perspective (false)?
		bool orthographic;

		int fieldOfView;
		float nearClipPlane;
		float farClipPlane;

		mutable Matrix4x4 projectionMatrix;

		Matrix4x4 GetViewMatrix() const;
		Matrix4x4 GetProjectMatrix() const;
	};
}

