#include "SpriteRenderer.h"
#include "../Graphics/VertexArray.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Graphics/SpriteVertex.h"

namespace Nuwa
{
	SpriteRenderer::SpriteRenderer()
	{
	}

	void SpriteRenderer::SetSprite(std::string path)
	{
		std::vector<SpriteVertex> vertices =
		{
			{ {  0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f } },
			{ { -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f } },
			{ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f } },
			{ {  0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f } }
		};

		std::vector<uint> indices =
		{
			0, 1, 2,
			0, 2, 3
		};

		GL_ASSERT(glEnable(GL_BLEND));
		GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		vao = std::make_unique<VertexArray>();		
		vbo = std::make_unique<VertexBuffer>(vertices.data(), sizeof(float) * vertices.size());

		VertexLayout layout;
		layout.Push<float>(3); // position
		layout.Push<float>(2); // uv

		vao->AddBuffer(*vbo, layout);

		ibo = std::make_unique<IndexBuffer>(indices.data(), sizeof(uint) * indices.size());

		shader = std::make_shared<Shader>("Resources/Shaders/Default.glsl");
		shader->Bind();
		shader->SetInt("tex", 0);

		texture = std::make_unique<Texture>(path);

		spritePath = path;
	}

	void SpriteRenderer::OnInspectorGUI()
	{
#ifdef NUWA_EDITOR
		EditorGUI::DrawLabel("Sprite Path", spritePath);
#endif // NUWA_EDITOR
	}
}