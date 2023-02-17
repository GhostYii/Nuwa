#pragma once
#include "BehaviorComponent.h"
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

	class MeshRenderer : public BehaviorComponent
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer() = default;

		void SetMesh(Mesh* mesh, const std::string& shaderPath, const std::string& texturePath);
		void SetCamera(Camera* camera);

		//Camera* drawCamera;

	protected:
		virtual void InternalRender() override;
		virtual void OnInspectorGUI() override;

	private:
		ToyRenderer renderer;

		std::shared_ptr<Camera> drawCamera;
		std::shared_ptr<Mesh> mesh;

		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<VertexBuffer> vbo;
		std::unique_ptr<IndexBuffer> ibo;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<Texture> texture;

		void Draw();
	};
}