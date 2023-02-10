#pragma once
#include "IBindable.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"

//class VertexLayout;
//class VertexBuffer;

namespace Nuwa
{
	class VertexArray :public IBindable
	{
	public:
		VertexArray();
		virtual ~VertexArray();

		void AddBuffer(const VertexBuffer& buffer, const VertexLayout& layout);

		// Inherited via IBindable
		virtual void Bind() const override;
		virtual void Unbind() const override;
	};

}