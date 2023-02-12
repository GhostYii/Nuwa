#pragma once
#include "../EngineMacros.h"
#include "../EngineTypes.h"

namespace Nuwa
{
	class GameObject;
	class Transform;

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

