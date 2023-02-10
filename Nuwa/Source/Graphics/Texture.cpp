#include "Texture.h"
#include "stb/stb_image.h"
#include "../EngineMacros.h"

Nuwa::Texture::Texture(const std::string& filepath)
	: filepath(filepath), localBuffer(nullptr), width(0), height(0), channel(0)
{
	stbi_set_flip_vertically_on_load(true);

	localBuffer = stbi_load(filepath.c_str(), &width, &height, &channel, BPP_COUNT_RGBA);

	GL_ASSERT(glGenTextures(1, &rendererID));
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, rendererID));

	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0));

	if (localBuffer)
		stbi_image_free(localBuffer);
}

Nuwa::Texture::~Texture()
{
	GL_ASSERT(glDeleteTextures(1, &rendererID));
}

void Nuwa::Texture::Bind() const
{
	GL_ASSERT(glActiveTexture(GL_TEXTURE0));
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, rendererID));
}

void Nuwa::Texture::Unbind() const
{
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0));
}

void Nuwa::Texture::Bind(uint slot) const
{
	GL_ASSERT(glActiveTexture(GL_TEXTURE0 + slot));
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, rendererID));
}
