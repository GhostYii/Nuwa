#include "VertexArray.h"
#include "../EngineMacros.h"

namespace Nuwa
{
	VertexArray::VertexArray()
	{
		GL_ASSERT(glGenVertexArrays(1, &rendererID));
	}

	VertexArray::~VertexArray()
	{
		Clear();
	}

	void VertexArray::Reset()
	{
		if (rendererID)
			Clear();

		GL_ASSERT(glGenVertexArrays(1, &rendererID));
	}

	void VertexArray::AddBuffer(const VertexBuffer& buffer, const VertexLayout& layout)
	{
		Bind();

		buffer.Bind();
		const auto& elements = layout.Elements();

		uint offset = 0;
		for (uint i = 0; i < elements.size(); ++i)
		{
			const auto& elem = elements[i];
			GL_ASSERT(glEnableVertexAttribArray(i));
			GL_ASSERT(glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, layout.Stride(), (const void*)offset));

			offset += elem.count * VertexElement::GetTypeSize(elem.type);
		}
	}

	void VertexArray::Bind() const
	{
		GL_ASSERT(glBindVertexArray(rendererID));
	}

	void VertexArray::Unbind() const
	{
		GL_ASSERT(glBindVertexArray(0));
	}

	void VertexArray::Clear()
	{
		GL_ASSERT(glDeleteVertexArrays(1, &rendererID));
	}
}