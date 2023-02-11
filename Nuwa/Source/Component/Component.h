#pragma once
#include "../EngineMacros.h"
#include "../EngineTypes.h"
#include "../GameObject.h"

namespace Nuwa
{
	class Component
	{
	public:
		Component();
		virtual ~Component() = default;		

		GameObject* gameObject;

	protected:
		uint64 instanceID;		
	};
}

