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

	private:
		void Create();

	private:
		uint width, height;
		std::vector<RenderTexture*> textureAttachments;
		std::vector<RenderBuffer*> bufferAttachments;
	};
}