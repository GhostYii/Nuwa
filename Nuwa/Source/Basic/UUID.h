#pragma once
#include "../EngineTypes.h"

namespace Nuwa
{
	class UUID 
	{
	public:
		UUID();
		UUID(uint64 uuid);
		UUID(const UUID&) = default;

		operator uint64() const { return uuid; }

		static uint64 Generate();

	private:
		uint64 uuid;
	};
}