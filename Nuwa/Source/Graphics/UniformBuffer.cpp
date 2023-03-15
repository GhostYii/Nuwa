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
		// ����glBindBufferBase�⣬Ҳ����ʹ��glBindBufferRange(GLenum target, GLuint index, GLuint buffer,	GLintptr offset, GLsizeiptr size);
		// ע��ú�����offset��������ΪGL_UNIFORM_BUFFER_OFFSET_ALIGNMENT�ı�����������ͨ�����·�ʽ��ȡ��
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
		// ע�⣺ʹ��glBufferSubData֮ǰ�����ȵ���glBufferData
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
		Unbind();
	}
	
	void UniformBuffer::SetData(const void* data, const uint size)
	{
		SetData(0, data, size);
	}
}