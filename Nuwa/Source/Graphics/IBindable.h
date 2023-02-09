#pragma once
#include "Renderer.h"

namespace Nuwa
{
	class IBindable
	{
	public:
		IBindable() : rendererID(0) {}
		virtual ~IBindable() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

	protected:
		uint rendererID;
	};
}