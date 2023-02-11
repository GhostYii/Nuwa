#include "Component.h"
#include "../Core/UUID.h"

Nuwa::Component::Component()
	: instanceID((uint64)Nuwa::UUID())
{
}
