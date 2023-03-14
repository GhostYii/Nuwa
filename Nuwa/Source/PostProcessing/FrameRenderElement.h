#pragma once
#include "../Graphics/VertexArray.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/VertexLayout.h"
#include "../Graphics/FrameBuffer.h"
#include "../Graphics/Shader.h"

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

		// ָ��fbo
		void Bind();
		// ��Ⱦ������
		void Draw();

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