#pragma once
#include "Transform.h"
#include "Component/Component.h"

namespace Nuwa
{	
#ifdef NUWA_EDITOR					
	namespace Editor
	{
		class Inspector;
	}
#endif // NUWA_EDITOR

	class GameObject
	{
		friend class GameScene;
#ifdef NUWA_EDITOR					
		friend class Editor::Inspector;
#endif // NUWA_EDITOR

	public:
		GameObject();
		GameObject(std::string name);
		//GameObject(const GameObject& other);
		virtual ~GameObject();

		std::string name;
		Transform transform;

		void SetActive(bool active);
		bool IsActive() const;

		void AddComponent(Component* component);

		template<typename T>
		T* GetComponent();

		template<typename T>
		std::vector<T*> GetComponents();

		template<typename T>
		std::vector<T*> GetBaseComponents();

		inline const uint64 GetInstanceID() const { return uuid; }

	private:
		uint64 uuid;
		bool isActive;
		// <typename, component>
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

	template<typename T>
	inline std::vector<T*> GameObject::GetBaseComponents()
	{
		std::vector<T*> res;

		for (auto iter : components)
		{
			auto com = dynamic_cast<T*>(iter.second);
			if (com)
				res.push_back(com);
		}

		return res;
	}

}

