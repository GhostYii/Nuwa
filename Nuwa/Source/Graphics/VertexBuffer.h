#pragma once
#include "IBindable.h"

namespace Nuwa
{
	class VertexBuffer : public IBindable
	{
	public:
		VertexBuffer(void* data, uint size);
		virtual ~VertexBuffer();		

		// Inherited via IBindable
		virtual void Bind() const override;
		virtual void Unbind() const override;	
		virtual void Clear() override;

		void Reset(void* data, uint size);
	};
}