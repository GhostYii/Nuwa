#include "Component.h"
#include "../GameObject.h"
#include "../Basic/UUID.h"

Nuwa::Component::Component()
	: instanceID((Nuwa::UUID::Generate())), gameObject(nullptr), transform(nullptr)
{
}

void Nuwa::Component::AttachToGameObject(GameObject* gameObject)
{
	if (!gameObject)
		return;

	gameObject->AddComponent(this);
}
