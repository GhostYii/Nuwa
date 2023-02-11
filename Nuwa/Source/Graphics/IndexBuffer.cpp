#include "IndexBuffer.h"
#include "../EngineMacros.h"

Nuwa::IndexBuffer::IndexBuffer(uint* data, uint count)
	: count(count)
{
	GL_ASSERT(glGenBuffers(1, &rendererID));
	GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
	GL_ASSERT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
}

void Nuwa::IndexBuffer::Bind() const
{
	GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
}

void Nuwa::IndexBuffer::Unbind() const
{
	GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

Nuwa::uint Nuwa::IndexBuffer::Count() const
{
	return count;
}
