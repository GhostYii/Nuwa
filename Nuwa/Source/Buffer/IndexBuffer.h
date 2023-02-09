#pragma once
#include "BufferBase.h"

namespace Nuwa
{
	class IndexBuffer : public BufferBase
	{
	public:
		IndexBuffer(const uint* data, uint count);
		virtual ~IndexBuffer() {}

		// Inherited via BufferBase
		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint count;
	};
}

