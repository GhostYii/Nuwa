#include "Transform.h"

Nuwa::Transform::Transform()
	: position(Vector3(0, 0, 0)), rotation(glm::radians(Vector3(0, 0, 0))), scale(Vector3(0, 0, 0)), eulerAngles(glm::eulerAngles(rotation))
{
}
