#include "VertexBuffer.h"
#include "../EngineMacros.h"

Nuwa::VertexBuffer::VertexBuffer(void* data, uint size)
{
	GL_ASSERT(glGenBuffers(1, &rendererID));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void Nuwa::VertexBuffer::Bind() const
{
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
}

void Nuwa::VertexBuffer::Unbind() const
{
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
