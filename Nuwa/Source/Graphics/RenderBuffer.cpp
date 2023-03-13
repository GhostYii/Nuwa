#include "RenderBuffer.h"
#include "../Global.h"

namespace Nuwa
{
	RenderBuffer::RenderBuffer()
		:width(Global::Resolution.x), height(Global::Resolution.y), isInited(false)
	{
		Create();
	}

	RenderBuffer::RenderBuffer(uint w, uint h)
		: width(w), height(h), isInited(false)
	{
		Create();
	}

	RenderBuffer::~RenderBuffer()
	{
		Clear();
	}

	void RenderBuffer::Bind() const
	{
		GL_ASSERT(glBindRenderbuffer(GL_RENDERBUFFER, rendererID));
		if (!isInited)
		{
			GL_ASSERT(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
			GL_ASSERT(glBindRenderbuffer(GL_RENDERBUFFER, GL_ZERO));

			GL_ASSERT(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rendererID));
			isInited = true;
		}
	}

	void RenderBuffer::Unbind() const
	{
		GL_ASSERT(glBindRenderbuffer(GL_RENDERBUFFER, GL_ZERO));		
	}

	void RenderBuffer::Clear()
	{
		Unbind();
		GL_ASSERT(glDeleteRenderbuffers(1, &rendererID));
	}

	void RenderBuffer::Bind(uint w, uint h)
	{
		width = w;
		height = h;

		Bind();
	}
	
	void RenderBuffer::Create()
	{
		GL_ASSERT(glGenRenderbuffers(1, &rendererID));
	}
}