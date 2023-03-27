#include "Renderer.h"
#include "Camera.h"

#include "../GameScene.h"
#include "../Graphics/GraphicTypes.h"

#include "../UBO.h"

namespace Nuwa
{
	//std::unique_ptr<UniformBuffer> Renderer::camMatUbo;

	Renderer::Renderer()
	{
		if (!UBO::CameraMatrix)
			UBO::CameraMatrix = std::make_unique<UniformBuffer>(sizeof(CamMatrix), UB_POINT_CAM_MAT);
	}

	Material* Renderer::GetMaterial() const
	{
		return material.get();
	}

	void Renderer::InternalRender()
	{
		if (!GameScene::mainCamera)
			return;

		if (!gameObject->IsActive())
			return;

		if (UBO::CameraMatrix)
		{
			UBO::CameraMatrix->SetData(0, glm::value_ptr(GameScene::mainCamera->GetProjectMatrix()), sizeof(Matrix4x4));
			UBO::CameraMatrix->SetData(sizeof(Matrix4x4), glm::value_ptr(GameScene::mainCamera->GetViewMatrix()), sizeof(Matrix4x4));
		}

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

		if (material)
		{
			material->SetUniformValue<Matrix4x4>("model", transform->GetModelMatrix());			
			material->SetUniformValue<Vector3>("camPos", GameScene::mainCamera->transform->position);

#ifdef NUWA_EDITOR
			material->SetUniformValue<Matrix4x4>("mvp.model", transform->GetModelMatrix());
			material->SetUniformValue<Matrix4x4>("mvp.view", GameScene::mainCamera->GetViewMatrix());
			material->SetUniformValue<Matrix4x4>("mvp.proj", GameScene::mainCamera->GetProjectMatrix());
#endif // NUWA_EDITOR

			material->Apply();
		}

		if (vao)
			vao->Bind();
		if (ibo)
			ibo->Bind();

		if (vao && ibo)
			GL_ASSERT(glDrawElements(GL_TRIANGLES, ibo->Count(), GL_UNSIGNED_INT, nullptr));
	}
}