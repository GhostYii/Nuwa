#include "Transform.h"
#include <glm/gtx/quaternion.hpp>

namespace Nuwa
{
	Transform::Transform()
		: position(Vector3(0, 0, 0)),
		rotation(Quaternion(glm::radians(Vector3(0, 0, 0)))),
		scale(Vector3(1, 1, 1))
		//roll(0), pitch(0), yaw(0)
	{
	}

	Vector3 Transform::Front()
	{
		Matrix4x4 mat = GetModelMatrix();
		Vector3 back = mat[2];
		return -glm::normalize(back);
	}

	Vector3 Transform::Right()
	{
		Matrix4x4 mat = GetModelMatrix();
		Vector3 right = mat[0];
		return glm::normalize(right);
	}

	Vector3 Transform::Up()
	{
		Matrix4x4 mat = GetModelMatrix();
		Vector3 up = mat[1];
		return glm::normalize(up);
	}

	Matrix4x4 Transform::GetModelMatrix() const
	{
		// srt
		Matrix4x4 model(1.0f);
		model = glm::translate(model, position) * glm::toMat4(rotation) * glm::scale(model, scale);
		return model;
	}
}
