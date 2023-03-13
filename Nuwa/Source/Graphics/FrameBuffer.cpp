#include "FrameBuffer.h"
#include "../EngineMacros.h"
#include "../Global.h"
#include "RenderTexture.h"
#include "RenderBuffer.h"

namespace Nuwa
{
	FrameBuffer::FrameBuffer()
		:width(Global::Resolution.x), height(Global::Resolution.y)
	{
		Create();
	}

	FrameBuffer::FrameBuffer(uint width, uint height)
		: width(width), height(height)
	{
		Create();
	}

	FrameBuffer::~FrameBuffer()
	{
		Clear();
	}

	void FrameBuffer::Bind() const
	{
		// unbind texture first
		//GL_ASSERT(glBindTexture(GL_TEXTURE_2D, GL_ZERO));
		GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));
		//GL_ASSERT(glViewport(0, 0, width, height));

		//uint pos = (uint)FrameAttatchmentType::Color0;
		//for (auto tex : textureAttachments)
		//	tex->Bind(pos++);

		//for (auto buf : bufferAttachments)
		//	buf->Bind();

		//spdlog::warn("frame buffer {} binded.", rendererID);
	}

	void FrameBuffer::Bind(const uint width, const uint height)
	{
		this->width = width;
		this->height = height;

		Bind();

		
	}

	void FrameBuffer::Unbind() const
	{
		GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, GL_ZERO));		
		//GL_ASSERT(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		//GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT));

		for (auto tex : textureAttachments)
			tex->Unbind();

		for (auto buf : bufferAttachments)
			buf->Unbind();

		//spdlog::warn("frame texture {} unbind.", rendererID);
	}

	void FrameBuffer::Clear()
	{
		Unbind();

		for (auto tex : textureAttachments)
			tex->Clear();

		for (auto buf : bufferAttachments)
			buf->Clear();

		GL_ASSERT(glDeleteFramebuffers(1, &rendererID));
	}

	void FrameBuffer::ApplyAttachments()
	{
		uint pos = (uint)FrameAttatchmentType::Color0;
		for (auto tex : textureAttachments)
			tex->Bind(pos++);

		for (auto buf : bufferAttachments)
			buf->Bind();
	}

	bool FrameBuffer::CheckState()
	{
		uint state;
		GL_ASSERT(state = glCheckFramebufferStatus(GL_FRAMEBUFFER));
		if (state != GL_FRAMEBUFFER_COMPLETE)
		{
			spdlog::error("create fbo failed, code {}", state);
			return false;
		}

		return true;
	}

	void FrameBuffer::AttachRenderTexture(uint width, uint height)
	{
		RenderTexture* rt = new RenderTexture(width, height);
		textureAttachments.push_back(rt);

		//rt->Bind();
	}

	void FrameBuffer::AttachRenderBuffer(uint width, uint height)
	{
		RenderBuffer* rb = new RenderBuffer(width, height);
		bufferAttachments.push_back(rb);

		//rb->Bind();
	}

	void FrameBuffer::Create()
	{
		GL_ASSERT(glGenFramebuffers(1, &rendererID));
		//Bind();
		//GL_ASSERT(glDrawBuffer(GL_COLOR_ATTACHMENT0));

		//spdlog::warn("frame buffer {} created.", rendererID);
	}
}