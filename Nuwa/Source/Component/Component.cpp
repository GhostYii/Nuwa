#include "Component.h"
#include "../Basic/UUID.h"

Nuwa::Component::Component()
	: instanceID((uint64)Nuwa::UUID())
{
}
