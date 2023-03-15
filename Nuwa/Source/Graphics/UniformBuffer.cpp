#include "UniformBuffer.h"
#include "Shader.h"

namespace Nuwa
{
	UniformBuffer::UniformBuffer(uint size, uint point)
		:bindingPoint(point)
	{
		GL_ASSERT(glGenBuffers(1, &rendererID));
		GL_ASSERT(glBindBuffer(GL_UNIFORM_BUFFER, rendererID));
		GL_ASSERT(glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW));
		Unbind();
	}

	UniformBuffer::~UniformBuffer()
	{
		Clear();
	}

	void UniformBuffer::Bind() const
	{
		GL_ASSERT(glBindBuffer(GL_UNIFORM_BUFFER, rendererID));
		GL_ASSERT(glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, rendererID));
		// 除了glBindBufferBase外，也可以使用glBindBufferRange(GLenum target, GLuint index, GLuint buffer,	GLintptr offset, GLsizeiptr size);
		// 注意该函数的offset参数必须为GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT的倍数，该数可通过如下方式获取：
		// uint uniformBufferOffsetAlign = 0;
		// glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &uniformBufferOffsetAlign);
	}

	void UniformBuffer::Unbind() const
	{
		GL_ASSERT(glBindBuffer(GL_UNIFORM_BUFFER, GL_ZERO));
	}

	void UniformBuffer::Clear()
	{
		Unbind();
		GL_ASSERT(glDeleteBuffers(1, &rendererID));
	}

	void UniformBuffer::Bind(uint point)
	{
		bindingPoint = point;
		Bind();
	}

	void UniformBuffer::Reset(uint size, uint point)
	{
		Bind(point);
		GL_ASSERT(glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW));
		Unbind();
	}

	void UniformBuffer::SetData(const uint offset, const void* data, const uint size)
	{
		Bind();
		// 注意：使用glBufferSubData之前必须先调用glBufferData
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
		Unbind();
	}
	
	void UniformBuffer::SetData(const void* data, const uint size)
	{
		SetData(0, data, size);
	}
}