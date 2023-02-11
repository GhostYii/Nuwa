#include "Camera.h"
#include "../Transform.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

namespace Nuwa
{
	Camera::Camera()
		: orthographic(false), fieldOfView(60), nearClipPlane(0.3f), farClipPlane(1000)
	{
		// TODO: width & height & radio
		projectionMatrix = orthographic ?
			glm::ortho(0.0f, 1366.0f, 0.0f, 768.0f, nearClipPlane, farClipPlane) :
			glm::perspective(glm::radians((float)fieldOfView), 1366.0f / 768.0f, nearClipPlane, farClipPlane);
	}

	Matrix4x4 Camera::GetViewMatrix() const
	{
		return orthographic ?
			glm::translate(glm::mat4(1.0f), transform->position) :
			glm::lookAt(transform->position, transform->position + transform->Front(), transform->Up());
	}

	Matrix4x4 Camera::GetProjectMatrix() const
	{
		return orthographic ?
			glm::ortho(0.0f, 1366.0f, 0.0f, 768.0f, nearClipPlane, farClipPlane) :
			glm::perspective(glm::radians((float)fieldOfView), 1366.0f / 768.0f, nearClipPlane, farClipPlane);
	}
}