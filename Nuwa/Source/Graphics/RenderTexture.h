#pragma once

#include "IBindable.h"

namespace Nuwa
{
	class RenderTexture : public IBindable
	{
	public:
		RenderTexture(uint width, uint height);
		virtual ~RenderTexture();

		// Inherited via IBindable
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Clear() override;

		void Bind(uint slot);

		//void SetPosition(uint pos);

	public:
		uint width;
		uint height;

	private:		
		uint attachIndex;
		mutable bool isInited;
	private:
		void Create();
	};
}