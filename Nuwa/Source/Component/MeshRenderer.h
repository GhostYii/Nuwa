#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "MeshFilter.h"
#include "../Mesh.h"
#include "../Graphics/ToyRenderer.h"

namespace Nuwa
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class Shader;
	class Texture;

	class MeshRenderer : public Renderer
	{
		friend class MeshFilter;
	public:
		MeshRenderer();
		virtual ~MeshRenderer() = default;

		void SetMaterial(Material* material);
		
	protected:
		virtual void Start() override;
		virtual void OnInspectorGUI() override;

	private:
		std::shared_ptr<Mesh> mesh;
		void ResetMeshDrawData(MeshFilter* filter);
	};
}