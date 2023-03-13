#pragma once
#include "../EngineTypes.h"
#include "../EngineMacros.h"

namespace Nuwa
{
	class IBindable
	{
	public:
		IBindable() : rendererID(0) {}
		virtual ~IBindable() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void Clear() = 0;

	protected:
		uint rendererID;
	};
}