#include "Component.h"
#include "../Basic/UUID.h"

Nuwa::Component::Component()
	: instanceID((Nuwa::UUID::Generate()))
{
}
