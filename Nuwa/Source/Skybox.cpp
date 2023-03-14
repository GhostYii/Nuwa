#include "Skybox.h"
#include "Graphics/ToyRenderer.h"
#include "Graphics/GraphicTypes.h"
#include "GameScene.h"
#include "Component/Camera.h"

namespace Nuwa
{
	std::vector<float> Skybox::vertices =
	{						 /* 		4--------5		*/
		-1.0f,  1.0f,  1.0f, /* 0		|\        \		*/
		 1.0f,  1.0f,  1.0f, /* 1		| \        \	*/
		 1.0f, -1.0f,  1.0f, /* 2		|  0--------1	*/
		-1.0f, -1.0f,  1.0f, /* 3		|  |        |	*/
		-1.0f,  1.0f, -1.0f, /* 4		7  |        |	*/
		 1.0f,  1.0f, -1.0f, /* 5		 \ |        |	*/
		 1.0f, -1.0f, -1.0f, /* 6		  \|        |	*/
		-1.0f, -1.0f, -1.0f	 /* 7		   3--------2	*/
	};

	std::vector<uint> Skybox::indices =
	{
		4, 7, 6,
		6, 5, 4,	//back
		3, 7, 4,
		4, 0, 3,	//left
		6, 2, 1,
		1, 5, 6,	//right
		3, 0, 1,
		1, 2, 3,	//front
		4, 5, 1,
		1, 0, 4,	//top
		7, 3, 6,
		6, 3, 2		//bottom
	};

	Skybox::Skybox()
		:filename("default"), vao(nullptr), ibo(nullptr), shader(nullptr), cubemap(nullptr)
	{
		Create();
	}

	Skybox::Skybox(std::string path)
		: filename(path), vao(nullptr), ibo(nullptr), shader(nullptr), cubemap(nullptr)
	{
		Create();
	}

	Skybox::~Skybox()
	{
		if (vao) vao->Clear();
		if (ibo) ibo->Clear();
		if (shader) shader->Clear();
		if (cubemap) cubemap->Clear();
	}

	void Skybox::Draw()
	{
		if (!vao || !GameScene::mainCamera)
			return;

		GL_ASSERT(glDepthFunc(GL_LEQUAL));
		cubemap->Bind();
		shader->SetMatrix4x4("projection", GameScene::mainCamera->GetProjectMatrix());
		shader->SetMatrix4x4("view", Matrix4x4(Matrix3x3(GameScene::mainCamera->GetViewMatrix())));
		ToyRenderer::Draw(vao, ibo, shader);
		GL_ASSERT(glDepthFunc(GL_LESS));
	}

	void Skybox::Create()
	{
		vao = new VertexArray();
		VertexBuffer* vbo = new VertexBuffer(vertices.data(), sizeof(float) * vertices.size());

		VertexLayout layout;
		layout.Push<float>(3);

		vao->AddBuffer(*vbo, layout);
		ibo = new IndexBuffer(indices.data(), sizeof(uint) * indices.size());

		shader = new Shader("Resources/Shaders/Skybox.shader");
		shader->SetInt("skybox", 0);

		cubemap = new CubeMap();
		cubemap->Load(filename);
	}
}