#pragma once
#include "IBindable.h"

namespace Nuwa
{
	class IndexBuffer : public IBindable
	{
	public:
		IndexBuffer(uint* data, uint count);
		virtual ~IndexBuffer();

		// Inherited via IBindable
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Clear() override;

		uint Count() const;
		void Reset(uint* data, uint count);

	private:
		uint count;
	};
}

