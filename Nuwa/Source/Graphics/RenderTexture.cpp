#include "RenderTexture.h"
#include "../EngineMacros.h"

namespace Nuwa
{
	RenderTexture::RenderTexture(uint width, uint height)
		:width(width), height(height), attachIndex((uint)FrameAttatchmentType::Color0), isInited(false)
	{
		Create();
	}

	RenderTexture::~RenderTexture()
	{
		Clear();
	}

	void RenderTexture::Bind() const
	{
		GL_ASSERT(glBindTexture(GL_TEXTURE_2D, rendererID));
		if (!isInited)
		{
			GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
			GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GL_ASSERT(glBindTexture(GL_TEXTURE_2D, GL_ZERO));

			GL_ASSERT(glFramebufferTexture2D(GL_FRAMEBUFFER, attachIndex, GL_TEXTURE_2D, rendererID, 0));
			isInited = true;
		}
	}

	void RenderTexture::Unbind() const
	{
		GL_ASSERT(glBindTexture(GL_TEXTURE_2D, GL_ZERO));
		GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, GL_ZERO));
	}

	void RenderTexture::Clear()
	{
		Unbind();
		glDeleteFramebuffers(1, &rendererID);
	}

	void RenderTexture::Bind(uint slot)
	{
		attachIndex = slot;
		Bind();
	}

	void RenderTexture::Create()
	{
		GL_ASSERT(glCreateTextures(GL_TEXTURE_2D, 1, &rendererID));
	}
}

