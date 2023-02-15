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
		: orthographic(false), fieldOfView(60), orthoSize(1.0),
		orthoClipPlane({ 0, 1000 }), perspClipPlane(Vector2(0.01f, 1000.0f))
	{
		float left = -1366.0f / 768.0f * orthoSize;
		float right = 1366.0f / 768.0f * orthoSize;
		float bottom = -orthoSize;
		float top = orthoSize;

		// TODO: width & height & radio
		projectionMatrix = orthographic ?
			glm::ortho(left, right, bottom, top, orthoClipPlane.x, orthoClipPlane.y) :
			glm::perspective(glm::radians((float)fieldOfView), 1366.0f / 768.0f, perspClipPlane.x, perspClipPlane.y);
	}

	Matrix4x4 Camera::GetViewMatrix() const
	{
		return orthographic ?
			glm::translate(glm::mat4(1.0f), transform->position) :
			glm::lookAt(transform->position, transform->position + transform->Front(), transform->Up());
	}

	Matrix4x4 Camera::GetProjectMatrix() const
	{
		float left = -1366.0f / 768.0f * orthoSize;
		float right = 1366.0f / 768.0f * orthoSize;
		float bottom = -orthoSize;
		float top = orthoSize;

		projectionMatrix = orthographic ?
			glm::ortho(left, right, bottom, top, orthoClipPlane.x, orthoClipPlane.y) :
			glm::perspective(glm::radians((float)fieldOfView), 1366.0f / 768.0f, perspClipPlane.x, perspClipPlane.y);

		return projectionMatrix;
	}
	
	void Camera::OnInspectorGUI()
	{
		
	}
}