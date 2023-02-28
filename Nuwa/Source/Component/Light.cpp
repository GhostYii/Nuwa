#include "Light.h"
#include "glm/gtc/type_ptr.hpp"
#include "../Graphics/Material.h"
#include "../GameScene.h"
#include "Renderer.h"
#include "../Global.h"

#ifdef NUWA_EDITOR
#include "../Editor/Component/GizmosRenderer.h"
#endif // NUWA_EDITOR

namespace Nuwa
{
	Light::Light()
		: ambient(0.1f), diffuse(1.0f), specular(1.0f), intensity(1.0f),
		color(Vector3(1.0f, 1.0f, 1.0f)), type(LightType::Direction)
	{
	}

	void Light::Start()
	{
#ifdef NUWA_EDITOR
		GizmosRenderer* gizmos = new GizmosRenderer("Resources/Editor/Icon/light_point.png");
		gameObject->AddComponent(gizmos);
#endif // NUWA_EDITOR
	}

	void Light::SetGameScene(GameScene* gameScene)
	{
		if (scene)
			return;

		scene = std::unique_ptr<GameScene>(gameScene);
	}

	void Light::InternalRender()
	{
		if (!scene)
			return;

//		auto objs = scene->GetAllGameObjects();
//		for (auto obj : objs)
//		{
//			auto renderList = obj->GetBaseComponents<Renderer>();
//			for (auto render : renderList) if (render && render->GetMaterial())
//			{
//				//spdlog::info("{}({}) render {} call.", obj->name, obj->GetInstanceID(), typeid(render).name());				
//				auto material = render->GetMaterial();
//				
//				material->SetUniformValue<float>("intensity", intensity);
//				material->SetUniformValue<Vector3>("lightColor", color);
//				material->SetUniformValue<Vector3>("lightPos", transform->position);
//
//#ifdef NUWA_EDITOR
//				material->SetUniformValue<Vector4>("gizmos.displayColor", Vector4(color, 1.0f));
//#endif // NUWA_EDITOR
//			}
//
//		}
	}

	void Light::OnEnable()
	{
		auto objs = scene->GetAllGameObjects();
		for (auto obj : objs)
		{
			auto renderList = obj->GetBaseComponents<Renderer>();
			for (auto render : renderList) if (render && render->GetMaterial())
			{
				auto material = render->GetMaterial();
				material->AddLight(this);
			}
		}
	}

	void Light::OnDisable()
	{
		auto objs = scene->GetAllGameObjects();
		for (auto obj : objs)
		{
			auto renderList = obj->GetBaseComponents<Renderer>();
			for (auto render : renderList) if (render && render->GetMaterial())
			{
				auto material = render->GetMaterial();
				material->RemoveLight(this);
			}
		}

//		auto objs = scene->GetAllGameObjects();
//		for (auto obj : objs)
//		{
//			auto renderList = obj->GetBaseComponents<Renderer>();
//			for (auto render : renderList) if (render && render->GetMaterial())
//			{
//				auto material = render->GetMaterial();
//
//				material->SetUniformValue<float>("intensity", intensity);
//				material->SetUniformValue<Vector3>("lightColor", color);
//				material->SetUniformValue<Vector3>("lightPos", transform->position);
//
//#ifdef NUWA_EDITOR
//				material->SetUniformValue<Vector4>("gizmos.displayColor", Vector4(color, 1.0f));
//#endif // NUWA_EDITOR
//			}
//		}
	}

	void Light::OnInspectorGUI()
	{
#ifdef NUWA_EDITOR
		EditorGUI::DrawEditColor3("Ambient Color", Global::AmbientColor);

		int val = (int)type;
		const char* items[] = { "Direction Light", "Point Light" };
		EditorGUI::DrawCombo("Type", &val, items, 2);
		type = (LightType)val;

		switch (type)
		{
		//case LightType::Environment:
		//	EditorGUI::DrawEditColor3("Color", color);
		//	EditorGUI::DrawSlideFloat("Intensity", intensity, 0, 10);
		//	break;
		case LightType::Direction:
			//ImGui::Text("Not Implement.");
			EditorGUI::DrawEditColor3("Color", color);
			break;
		case LightType::Point:			
			EditorGUI::DrawEditColor3("Color", color);
			break;
		default:
			ImGui::Text("Not Implement.");
			break;
		}
#endif
	}


}