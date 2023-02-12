#include "GameObject.h"
#include "Basic/UUID.h"

namespace Nuwa
{
	GameObject::GameObject()
		: name("game object"), uuid(UUID::Generate()), transform(Transform())
	{

	}

	GameObject::~GameObject()
	{
		//for (auto& pCom : components)
		//	pCom.reset();
	}

	void GameObject::AddComponent(Component* component)
	{
		const std::string typeName = typeid(*component).name();
		for (auto iter = components.find(typeName); iter != components.end() && iter->first == typeName; iter++)
		{
			if (iter->second->GetInstanceID() == component->GetInstanceID())
				return;
		}

		component->gameObject = this;
		component->transform = &(this->transform);
		components.emplace(typeid(*component).name(), component);
	}

	

	
}
