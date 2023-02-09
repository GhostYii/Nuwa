#include "IndexBuffer.h"

Nuwa::IndexBuffer::IndexBuffer(const uint* data, uint count)
	: count(count)
{
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW);
}

void Nuwa::IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}

void Nuwa::IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
