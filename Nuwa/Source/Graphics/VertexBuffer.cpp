#include "VertexBuffer.h"

Nuwa::VertexBuffer::VertexBuffer(const void* data, uint size)
{
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Nuwa::VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void Nuwa::VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
