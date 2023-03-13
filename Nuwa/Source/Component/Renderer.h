#pragma once
#include "BehaviorComponent.h"
#include "../Mesh.h"

namespace Nuwa
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class Shader;
	class Texture;
	class Material;

	class Renderer : public BehaviorComponent
	{
	public:
		Renderer();
		virtual ~Renderer() = default;

		Material* GetMaterial() const;

	protected:
		virtual void InternalRender() override;
		virtual void OnInspectorGUI() override;

		// TODO: Multi-Materials
		std::shared_ptr<Material> material;

		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<VertexBuffer> vbo;
		std::unique_ptr<IndexBuffer> ibo;		

		virtual void Draw();
	};
}