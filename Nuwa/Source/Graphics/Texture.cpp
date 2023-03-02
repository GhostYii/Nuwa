#include "Texture.h"
#include "stb/stb_image.h"
#include "../EngineMacros.h"

namespace Nuwa
{
	Texture::Texture(const std::string& filepath)
		: filepath(filepath), localBuffer(nullptr), width(0), height(0), channel(0)
	{
		stbi_set_flip_vertically_on_load(true);

		localBuffer = stbi_load(filepath.c_str(), &width, &height, &channel, 0);

		GLenum format;
		if (channel == 1)
			format = GL_RED;
		else if (channel == 3)
			format = GL_RGB;
		else if (channel == 4)
			format = GL_RGBA;

		GL_ASSERT(glGenTextures(1, &rendererID));
		GL_ASSERT(glBindTexture(GL_TEXTURE_2D, rendererID));

		GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, localBuffer));
		GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D));
		GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0));

		if (localBuffer)
			stbi_image_free(localBuffer);
	}

	Texture::~Texture()
	{
		Clear();
	}

	void Texture::Bind() const
	{
		GL_ASSERT(glActiveTexture(GL_TEXTURE0));
		GL_ASSERT(glBindTexture(GL_TEXTURE_2D, rendererID));
	}

	void Texture::Unbind() const
	{
		GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void Texture::Clear()
	{
		GL_ASSERT(glDeleteTextures(1, &rendererID));
	}

	void Texture::Bind(uint slot) const
	{
		GL_ASSERT(glActiveTexture(GL_TEXTURE0 + slot));
		GL_ASSERT(glBindTexture(GL_TEXTURE_2D, rendererID));
	}

}
