#pragma once
#include "../EngineMacros.h"
#include "../EngineTypes.h"

namespace Nuwa
{
	class Component
	{
	public:
		Component();
		virtual ~Component() = default;

	protected:
		uint64 instanceID;
	};
}

