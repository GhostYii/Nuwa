#pragma once
#include "IBindable.h"

namespace Nuwa
{
	class RenderTexture;
	class RenderBuffer;

	class FrameBuffer : public IBindable
	{
	public:
		FrameBuffer();
		FrameBuffer(uint width, uint height);
		virtual ~FrameBuffer();

		// Inherited via IBindable
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Clear() override;

		virtual void Bind(const uint width, const uint height);

		void ApplyAttachments();

		bool CheckState();

		void AttachRenderTexture(uint width, uint height);
		void AttachRenderBuffer(uint width, uint height);		

		//void Apply();

		//static uint CreateTextureAttachment(int width, int height);
		//static uint* CreateColorAttachments(int width, int height, unsigned int nColorAttachments);
		//static uint CreateDepthTextureAttachment(int width, int height);
		//static uint CreateDepthBufferAttachment(int width, int height);
		//static uint CreateRenderBufferAttachment(int width, int height);

	private:
		void Create();
		
	private:
		uint width, height;
		std::vector<RenderTexture*> textureAttachments;
		std::vector<RenderBuffer*> bufferAttachments;
	};
}