#include "FrameRenderElement.h"
#include "ToyRenderer.h"

namespace Nuwa
{
	FrameRenderElement::FrameRenderElement(uint width, uint height)
		: width(width), height(height)
	{						
		std::vector<FrameVertex> vertices =
		{
			{ {  1.0f,  1.0f }, { 1.0f, 1.0f } },
			{ { -1.0f,  1.0f }, { 0.0f, 1.0f } },
			{ { -1.0f, -1.0f }, { 0.0f, 0.0f } },
			{ {  1.0f, -1.0f }, { 1.0f, 0.0f } }
		};

		std::vector<uint> indices =
		{
			0, 1, 2,
			0, 2, 3
		};

		//GL_ASSERT(glEnable(GL_BLEND));
		//GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		fbo = std::make_shared<FrameBuffer>(width, height);		
		fbo->Bind();		

		fbo->AttachRenderTexture(width, height);
		//fbo->AttachRenderBuffer(width, height);

		fbo->ApplyAttachments();

		if (!fbo->CheckState())
		{
			fbo->Clear();
			return;
		}

		fbo->Unbind();

		vao = std::make_shared<VertexArray>();
		vbo = std::make_shared<VertexBuffer>(vertices.data(), sizeof(float) * vertices.size());

		VertexLayout layout;
		layout.Push<float>(2); // position
		layout.Push<float>(2); // texcoord

		vao->AddBuffer(*vbo, layout);

		ibo = std::make_shared<IndexBuffer>(indices.data(), sizeof(uint) * indices.size());

		postShader = std::make_shared<Shader>("Resources/Shaders/DefaultPost.vert", "Resources/Shaders/DefaultPost.frag");
		
		postShader->SetInt("renderTexture", 0);
	}

	FrameRenderElement::~FrameRenderElement()
	{
		vao->Clear();
		vbo->Clear();
		ibo->Clear();
		fbo->Clear();
		postShader->Clear();
	}

	void FrameRenderElement::Bind()
	{
		if (!fbo)
			return;

		fbo->Bind();
		GL_ASSERT(glEnable(GL_DEPTH_TEST));

		// TODO: save to config or camera
		GL_ASSERT(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void FrameRenderElement::DrawToTexture()
	{
		if (!fbo)
			return;
	
		fbo->Unbind();

		GL_ASSERT(glDisable(GL_DEPTH_TEST));

		GL_ASSERT(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT));
		
		fbo->ApplyAttachments();

		ToyRenderer::Draw(vao.get(), ibo.get(), postShader.get());
	}
}