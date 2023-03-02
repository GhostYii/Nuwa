#include "VertexBuffer.h"
#include "../EngineMacros.h"

namespace Nuwa
{
	VertexBuffer::VertexBuffer(void* data, uint size)
	{
		GL_ASSERT(glGenBuffers(1, &rendererID));
		GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
		GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	VertexBuffer::~VertexBuffer()
	{
		Clear();
	}

	void VertexBuffer::Bind() const
	{
		GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
	}

	void VertexBuffer::Unbind() const
	{
		GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VertexBuffer::Clear()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void VertexBuffer::Reset(void* data, uint size)
	{
		if (rendererID)
			Clear();

		GL_ASSERT(glGenBuffers(1, &rendererID));
		GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
		GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}
}
