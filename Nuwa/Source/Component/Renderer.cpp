#include "Renderer.h"

#include "../Transform.h"
#include "../GameObject.h"
#include "../Graphics/VertexArray.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"

namespace Nuwa
{
	Renderer::Renderer()
		:renderer(ToyRenderer())
	{
	}

	void Renderer::SetCamera(Camera* camera)
	{
		drawCamera = std::shared_ptr<Camera>(camera);
	}

	Shader* Renderer::GetShader() const
	{
		return shader.get();
	}

	void Renderer::InternalRender()
	{
		if (!drawCamera)
			return;
		
		if (!gameObject->IsActive())
			return;

		Draw();
	}

	void Renderer::OnInspectorGUI()
	{
	}

	void Renderer::Draw()
	{
		//if (!drawCamera)
		//	return;

		if (texture)
			texture->Bind();

		if (shader)
		{
			shader->Bind();
			shader->SetMatrix4x4("model", transform->GetModelMatrix());
			shader->SetMatrix4x4("camMatrix", drawCamera->GetProjectMatrix() * drawCamera->GetViewMatrix());			
		}

		if (vao)
			vao->Bind();
		if (ibo)
			ibo->Bind();

		if (vao && ibo)
			GL_ASSERT(glDrawElements(GL_TRIANGLES, ibo->Count(), GL_UNSIGNED_INT, nullptr));
	}
}