#pragma once
#include "Component.h"
#include "../Mesh.h"
#include "../Graphics/Renderer.h"
#include "Camera.h"

namespace Nuwa
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class Shader;
	class Texture;

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer() = default;

		void SetMesh(Mesh* mesh, const std::string& shaderPath, const std::string& texturePath);

		void Draw(const Camera& camera);

	private:
		ToyRenderer renderer;

		std::shared_ptr<Mesh> mesh;

		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<VertexBuffer> vbo;
		std::unique_ptr<IndexBuffer> ibo;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<Texture> texture;
	};
}