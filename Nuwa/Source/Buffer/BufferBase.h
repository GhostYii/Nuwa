#pragma once
#include "../Renderer.h"

namespace Nuwa
{
	class BufferBase
	{
	public:
		BufferBase() : rendererID(0) {}
		virtual ~BufferBase() { glDeleteBuffers(1, &rendererID); }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

	protected:
		uint rendererID;
	};
}