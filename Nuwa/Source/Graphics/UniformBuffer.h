#pragma once
#include "IBindable.h"

namespace Nuwa
{
	class Shader;
	class UniformBuffer : public IBindable
	{
	public:
		UniformBuffer(uint size, uint point);
		virtual ~UniformBuffer();

		// Inherited via IBindable
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Clear() override;

		void Bind(uint point);
		void Reset(uint size, uint point);
		void SetData(const uint offset, const void* data, const uint size);		
		void SetData(const void* data, const uint size);

	private:
		uint bindingPoint;
	};
}