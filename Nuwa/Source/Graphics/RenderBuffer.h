#pragma once
#include "IBindable.h"

namespace Nuwa
{
	class RenderBuffer : public IBindable
	{
	public:
		RenderBuffer();
		RenderBuffer(uint w, uint h);
		virtual ~RenderBuffer();

		// Inherited via IBindable
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Clear() override;

		void Bind(uint w, uint h);

		inline uint GetRenderID() { return rendererID; }

	private:
		void Create();

	private:
		uint width, height;
		//uint frameBufferID;
		mutable bool isInited;
	};
}
