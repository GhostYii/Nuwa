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

		template<typename T>
		std::vector<T*> GetComponents();

		inline const uint64 GetInstanceID() const { return uuid; }

	private:
		uint64 uuid;
		//std::vector<Component*> components;
		std::unordered_multimap<std::string, Component*> components;
	};

	template<typename T>
	inline T* GameObject::GetComponent()
	{
		const std::string typeName = typeid(T).name();
		if (components.count(typeName))
			return dynamic_cast<T*>(components.find(typeName)->second);

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> GameObject::GetComponents()
	{
		std::vector<T*> res;

		const std::string typeName = typeid(T).name();
		for (auto iter = components.find(typeName); iter != components.end() && iter->first == typeName; iter++)
			res.push_back(dynamic_cast<T*>(iter->second));

		return res;
	}

}

