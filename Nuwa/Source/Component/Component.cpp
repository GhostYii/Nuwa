#include "Component.h"
#include "../GameObject.h"
#include "../Basic/UUID.h"

namespace Nuwa
{
	Component::Component()
		: instanceID((Nuwa::UUID::Generate())), gameObject(nullptr), transform(nullptr)
	{
	}

	void Component::AttachToGameObject(GameObject* gameObject)
	{
		if (!gameObject)
			return;

		gameObject->AddComponent(this);
	}

	const uint64 Component::GetInstanceID() const
	{
		return instanceID;
	}
}