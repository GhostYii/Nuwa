#pragma once
#include "BehaviorComponent.h"
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

	class Renderer : public BehaviorComponent
	{
	public:
		Renderer();
		virtual ~Renderer() = default;

		void SetCamera(Camera* camera);
		Shader* GetShader() const;

	protected:
		virtual void InternalRender() override;
		virtual void OnInspectorGUI() override;

		// TODO: Material
		ToyRenderer renderer;

		std::shared_ptr<Camera> drawCamera;
		std::shared_ptr<Shader> shader;

		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<VertexBuffer> vbo;
		std::unique_ptr<IndexBuffer> ibo;		
		std::unique_ptr<Texture> texture;
		
		virtual void Draw();
	};
}