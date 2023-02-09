#pragma once
#include "IBindable.h"

namespace Nuwa
{
	class IndexBuffer : public IBindable
	{
	public:
		IndexBuffer(const uint* data, uint count);
		virtual ~IndexBuffer() { glDeleteBuffers(1, &rendererID); }

		// Inherited via IBindable
		virtual void Bind() const override;
		virtual void Unbind() const override;

		uint Count() const;

	private:
		uint count;
	};
}

