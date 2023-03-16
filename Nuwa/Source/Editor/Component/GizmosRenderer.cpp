#ifdef NUWA_EDITOR

#include "GizmosRenderer.h"
#include "../../Graphics/GraphicTypes.h"
#include "../../GameObject.h"

namespace Nuwa
{
	namespace Editor
	{
		GizmosRenderer::GizmosRenderer(std::string iconPath)
			: path(iconPath)
		{
			float vPos = 0.2f;
			std::vector<SpriteVertex> vertices =
			{
				{ {  vPos,  vPos, 0.0f }, { 1.0f, 1.0f } },
				{ { -vPos,  vPos, 0.0f }, { 0.0f, 1.0f } },
				{ { -vPos, -vPos, 0.0f }, { 0.0f, 0.0f } },
				{ {  vPos, -vPos, 0.0f }, { 1.0f, 0.0f } }
			};

			std::vector<uint> indices =
			{
				0, 1, 2,
				0, 2, 3
			};

			GL_ASSERT(glEnable(GL_BLEND));
			GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

			vao = std::make_unique<VertexArray>();
			vbo = std::make_unique<VertexBuffer>(vertices.data(), sizeof(SpriteVertex) * vertices.size());

			VertexLayout layout;
			layout.Push<float>(3); // position
			layout.Push<float>(2); // uv

			vao->AddBuffer(*vbo, layout);

			ibo = std::make_unique<IndexBuffer>(indices.data(), sizeof(uint) * indices.size());

			material = std::make_shared<Material>(new Shader("Resources/Editor/Shader/gizmos.vert", "Resources/Editor/Shader/gizmos.frag"));
			material->SetUniformValue<int>("gizmos.tex", ALBEDO_MAP_INDEX);
			material->SetUniformValue<Vector4>("gizmos.displayColor", Vector4(1.0));

			material->SetAlbedoMap(iconPath);
		}

		GizmosRenderer::~GizmosRenderer()
		{
		}

		void GizmosRenderer::InternalRender()
		{
			if (EditorMode::isShowGizmos)
				Renderer::InternalRender();
		}
	}
}

#endif // NUWA_EDITOR