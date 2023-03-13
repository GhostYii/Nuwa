#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexLayout.h"
#include "FrameBuffer.h"
#include "Shader.h"

namespace Nuwa
{
	class FrameRenderElement
	{
		struct FrameVertex
		{
			Vector2 position;
			Vector2 texcoord;
		};

	public:
		FrameRenderElement(uint width, uint height);
		~FrameRenderElement();

		// 指定fbo
		void Bind();
		// 渲染到纹理
		void DrawToTexture();

	public:
		uint width, height;

	private:		
		std::shared_ptr<VertexArray> vao;
		std::shared_ptr<VertexBuffer> vbo;
		std::shared_ptr<IndexBuffer> ibo;
		std::shared_ptr<FrameBuffer> fbo;

		std::shared_ptr<Shader> postShader;
	};
}