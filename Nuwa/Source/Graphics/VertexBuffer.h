#pragma once
#include "IBindable.h"

namespace Nuwa
{
	class VertexBuffer : public IBindable
	{
	public:
		VertexBuffer(const void* data, uint size);
		virtual ~VertexBuffer() { glDeleteBuffers(1, &rendererID); }

		// Inherited via IBindable
		virtual void Bind() const override;
		virtual void Unbind() const override;	
	};
}