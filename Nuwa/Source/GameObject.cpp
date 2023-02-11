#include "GameObject.h"
#include "Basic/UUID.h"

Nuwa::GameObject::GameObject()
	: name("game object"), uuid(UUID::Generate()), transform(Transform())
{

}

Nuwa::GameObject::~GameObject()
{
	//for (auto& pCom : components)
	//	pCom.reset();
}

void Nuwa::GameObject::AddComponent(Component* component)
{
	component->gameObject = this;
	component->transform = &(this->transform);

	// TODO: ÷ÿ∏¥ºÏ≤‚
	components.push_back(std::make_shared<Component>(*component));	
}
