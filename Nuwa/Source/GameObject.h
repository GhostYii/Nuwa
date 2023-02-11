#pragma once
#include "Component/Transform.h"

namespace Nuwa
{
	class GameObject
	{
	public:
		GameObject();
		//GameObject(const GameObject& other);
		virtual ~GameObject();

		std::string name;
		Transform transform;

		void AddComponent(Component* component);

	private:
		uint64 uuid;
		std::vector<std::shared_ptr<Component>> components;
	};
}

