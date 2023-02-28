#pragma once
#include "Renderer.h"
#include "../Mesh.h"
#include "../Graphics/ToyRenderer.h"
#include "Camera.h"

namespace Nuwa
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class Shader;
	class Texture;

	class MeshRenderer : public Renderer
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer() = default;

		void SetMesh(Mesh* mesh, const std::string& shaderPath);
		void SetMesh(Mesh* mesh, const std::string& vertShader, const std::string& fragShader);

	protected:
		virtual void OnInspectorGUI() override;

	private:
		std::shared_ptr<Mesh> mesh;
	};
}