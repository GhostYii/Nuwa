#pragma once
#include "BufferBase.h"

namespace Nuwa
{
	class VertexBuffer : public BufferBase
	{
	public:
		VertexBuffer(const void* data, uint size);
		virtual ~VertexBuffer() {}

		// Inherited via BufferBase
		virtual void Bind() const override;
		virtual void Unbind() const override;	
	};
}