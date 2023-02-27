#pragma once
#include "BehaviorComponent.h"

namespace Nuwa
{
	class Camera : public BehaviorComponent
	{
	public:
		Camera();
		virtual ~Camera() = default;

		// Is the camera orthographic (true) or perspective (false)?
		bool orthographic;

		int fieldOfView;
		float orthoSize;
		//float nearClipPlane;
		//float farClipPlane;

		mutable Matrix4x4 projectionMatrix;

		Matrix4x4 GetViewMatrix() const;
		Matrix4x4 GetProjectMatrix() const;

		inline float GetNearClipPlane() const { return orthographic ? orthoClipPlane.x : perspClipPlane.x; }
		inline float GetFarClipPlane() const { return orthographic ? orthoClipPlane.y : perspClipPlane.y; }

		inline void SetClipPlane(const float zNear, const float zFar)
		{
			if (orthographic)
				orthoClipPlane = Vector2(zNear, zFar);
			else
				perspClipPlane = Vector2(zNear, zFar);
		}

		virtual void Awake() override;

	protected:
		virtual void OnInspectorGUI() override;

	private:
		Vector2 orthoClipPlane;
		Vector2 perspClipPlane;
	};
}

