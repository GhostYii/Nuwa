#include "Texture.h"
#include "stb/stb_image.h"
#include "../EngineMacros.h"

Nuwa::Texture::Texture(const std::string& filepath)
	: filepath(filepath), localBuffer(nullptr), width(0), height(0), channel(0)
{
	stbi_set_flip_vertically_on_load(true);

	localBuffer = stbi_load(filepath.c_str(), &width, &height, &channel, BPP_COUNT_RGBA);

	glGenTextures(1, &rendererID);
	glBindTexture(GL_TEXTURE_2D, rendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (localBuffer)
		stbi_image_free(localBuffer);
}

Nuwa::Texture::~Texture()
{
	glDeleteTextures(1, &rendererID);
}

void Nuwa::Texture::Bind() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, rendererID);
}

void Nuwa::Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Nuwa::Texture::Bind(uint slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, rendererID);
}
