#ifdef NUWA_EDITOR
#include "InfiniteGridRenderer.h"
#include "../../Graphics/GraphicTypes.h"

namespace Nuwa
{
	namespace Editor
	{
		InfiniteGridRenderer::InfiniteGridRenderer()
		{
			std::vector<Vector3> vertices =
			{
				{  1, 1, 0 }, {  -1, -1, 0 },
				{  -1,  1, 0 }, { 1,  -1, 0 }
			};

			std::vector<uint> indices =
			{
				0, 2, 1,
				1, 3, 0
			};			

			GL_ASSERT(glEnable(GL_DEPTH_TEST));
			GL_ASSERT(glEnable(GL_BLEND));
			GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

			vao = std::make_unique<VertexArray>();
			vbo = std::make_unique<VertexBuffer>(vertices.data(), sizeof(Vector3) * vertices.size());

			VertexLayout layout;
			layout.Push<float>(3);

			vao->AddBuffer(*vbo, layout);

			ibo = std::make_unique<IndexBuffer>(indices.data(), sizeof(uint) * indices.size());			

			material = std::make_shared<Material>(new Shader("Resources/Editor/Shader/infinite_grid.shader"));
		}

		InfiniteGridRenderer::~InfiniteGridRenderer()
		{

		}

		//void InfiniteGridRenderer::InternalRender()
		//{
		//	Renderer::InternalRender();
		//}
	}
}

#endif // NUWA_EDITOR