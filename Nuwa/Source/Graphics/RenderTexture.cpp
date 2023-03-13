#include "RenderTexture.h"
#include "../EngineMacros.h"

namespace Nuwa
{
	RenderTexture::RenderTexture(uint width, uint height)
		:width(width), height(height), attachIndex((uint)FrameAttatchmentType::Color0),
		 isInited(false)
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
			GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
			GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			//GL_ASSERT(glBindTexture(GL_TEXTURE_2D, GL_ZERO));

			GL_ASSERT(glFramebufferTexture2D(GL_FRAMEBUFFER, attachIndex, GL_TEXTURE_2D, rendererID, 0));
			isInited = true;

			//spdlog::warn("render texture {} inited.", rendererID);
		}

		//spdlog::warn("render texture {} binded.", rendererID);
	}

	void RenderTexture::Unbind() const
	{
		GL_ASSERT(glBindTexture(GL_TEXTURE_2D, GL_ZERO));
		GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, GL_ZERO));
		//spdlog::warn("render texture {} unbind.", rendererID);
	}

	void RenderTexture::Clear()
	{
		Unbind();
		glDeleteFramebuffers(1, &rendererID);
		//glDeleteTextures(1, )
	}

	void RenderTexture::Bind(uint slot)
	{
		attachIndex = slot;
		Bind();		
	}

	//void RenderTexture::SetPosition(uint pos)
	//{
	//	attachIndex = pos;
	//}

	void RenderTexture::Create()
	{
		GL_ASSERT(glGenTextures(1, &rendererID));
		//Bind();

		//spdlog::warn("render texture {} created.", rendererID);
	}
}

