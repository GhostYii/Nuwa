#include "CubeMap.h"
#include "stb/stb_image.h"

namespace Nuwa
{
	CubeMap::CubeMap()
	{
		GL_ASSERT(glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &rendererID));
	}

	CubeMap::~CubeMap()
	{
		Clear();
	}

	void CubeMap::Bind() const
	{
		GL_ASSERT(glActiveTexture(GL_TEXTURE0));
		GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, rendererID));
	}

	void CubeMap::Unbind() const
	{
		GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	}

	void CubeMap::Clear()
	{
		Unbind();
		GL_ASSERT(glDeleteTextures(1, &rendererID));
	}

	void CubeMap::Load(std::string& path)
	{
		Bind();

		// TODO: ignore extension
		// 该顺序与下方循环顺序对应，如需改变应该同时变
		const std::vector<std::string> faces =
		{
			"right.jpg",
			"left.jpg",
			"top.jpg",
			"bottom.jpg",
			"back.jpg",
			"front.jpg"
		};

		uint index = 0;
		for (auto& face : faces)
		{
			int width, height, channel;
			std::string filename = spdlog::fmt_lib::format("Resources/Textures/Skybox/{}/{}", path, face);			
			uchar* data = stbi_load(filename.c_str(), &width, &height, &channel, 0);
			if (data)
			{
				GLenum format;
				switch (channel)
				{
				case 1:	format = GL_RED; break;
				case 3: format = GL_RGB; break;
				case 4: format = GL_RGBA; break;
				default: format = GL_RGB; break;
				}

				GL_ASSERT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index++, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
			}
			else
			{
				spdlog::error("load cube map {} failed.", filename);
				stbi_image_free(data);
				Clear();
				return;
			}
			stbi_image_free(data);
		}

		GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	}
}