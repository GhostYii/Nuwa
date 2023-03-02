#include "IndexBuffer.h"
#include "../EngineMacros.h"

namespace Nuwa
{
	IndexBuffer::IndexBuffer(uint* data, uint count)
		: count(count)
	{
		GL_ASSERT(glGenBuffers(1, &rendererID));
		GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
		GL_ASSERT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		Clear();
	}

	void IndexBuffer::Bind() const
	{
		GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
	}

	void IndexBuffer::Unbind() const
	{
		GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	uint IndexBuffer::Count() const
	{
		return count;
	}

	void IndexBuffer::Reset(uint* data, uint count)
	{
		if (rendererID)
			Clear();

		GL_ASSERT(glGenBuffers(1, &rendererID));
		GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
		GL_ASSERT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW));
	}

	void IndexBuffer::Clear()
	{
		GL_ASSERT(glDeleteBuffers(1, &rendererID));
	}
}

