#pragma once
#include "IBindable.h"
#include <string>

namespace Nuwa
{
	class Texture : public IBindable
	{
	public:
		Texture(const std::string& filepath);
		virtual ~Texture();

		// Inherited via IBindable
		virtual void Bind() const override;
		virtual void Unbind() const override;

		void Bind(uint slot) const;

		inline int Width() { return width; }
		inline int Height() { return height; }
	private:
		std::string filepath;
		uchar* localBuffer;
		int width;
		int height;
		// bits per-pixel of texture
		int channel;
	};
}

