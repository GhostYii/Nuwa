#include "VertexArray.h"
#include "../EngineMacros.h"

Nuwa::VertexArray::VertexArray()
{
	GL_ASSERT(glGenVertexArrays(1, &rendererID));
}

Nuwa::VertexArray::~VertexArray()
{
	GL_ASSERT(glDeleteVertexArrays(1, &rendererID));
}

void Nuwa::VertexArray::AddBuffer(const VertexBuffer& buffer, const VertexLayout& layout)
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

void Nuwa::VertexArray::Bind() const
{
	GL_ASSERT(glBindVertexArray(rendererID));
}

void Nuwa::VertexArray::Unbind() const
{
	GL_ASSERT(glBindVertexArray(0));
}
