#include "Renderer.h"
#include "Camera.h"

#include "../GameScene.h"
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

	//void Renderer::SetCamera(Camera* camera)
	//{
	//	drawCamera = std::shared_ptr<Camera>(camera);
	//}

	Shader* Renderer::GetShader() const
	{
		return shader.get();
	}

	void Renderer::InternalRender()
	{
		if (!GameScene::mainCamera)
			return;

		if (!gameObject->IsActive())
			return;

		Draw();
	}

	void Renderer::OnInspectorGUI()
	{
#ifdef NUWA_EDITOR

#endif // NUWA_EDITOR

	}

	void Renderer::Draw()
	{
		//if (!GameScene::mainCamera)
		//	return;

		if (texture)
			texture->Bind();

		if (shader)
		{
			shader->Bind();
			shader->SetMatrix4x4("model", transform->GetModelMatrix());
			shader->SetMatrix4x4("camMatrix", GameScene::mainCamera->GetProjectMatrix() * GameScene::mainCamera->GetViewMatrix());
			shader->SetVector3("camPos", GameScene::mainCamera->transform->position);

#ifdef NUWA_EDITOR
			shader->SetMatrix4x4("mvp.model", transform->GetModelMatrix());
			shader->SetMatrix4x4("mvp.view", GameScene::mainCamera->GetViewMatrix());
			shader->SetMatrix4x4("mvp.proj", GameScene::mainCamera->GetProjectMatrix());
#endif // NUWA_EDITOR

		}

		if (vao)
			vao->Bind();
		if (ibo)
			ibo->Bind();

		if (vao && ibo)
			GL_ASSERT(glDrawElements(GL_TRIANGLES, ibo->Count(), GL_UNSIGNED_INT, nullptr));
	}
}