#pragma once
#include "../EngineMacros.h"
#include "../EngineTypes.h"
#include "../Transform.h"

namespace Nuwa
{
	class GameObject;
	
	class Component
	{
	public:
		Component();
		virtual ~Component() = default;

		GameObject* gameObject;
		Transform* transform;

		void AttachToGameObject(GameObject* gameObject);

		const uint64 GetInstanceID() const;

	protected:
		uint64 instanceID;
	};
}

