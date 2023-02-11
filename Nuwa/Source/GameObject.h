#pragma once
#include "Transform.h"
#include "Component/Component.h"

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

		template<typename T>
		T* GetComponent();

	private:
		uint64 uuid;
		std::vector<std::shared_ptr<Component>> components;
	};


	template<typename T>
	inline T* GameObject::GetComponent()
	{
		for (const auto& iter : components)
		{			
			//spdlog::info("type1 {}, type2 {}", typeid(*iter).name(), typeid(T).name());

			if (typeid(*iter) == typeid(T))
				return static_cast<T*>(iter.get());
		}
		return nullptr;
	}
}

