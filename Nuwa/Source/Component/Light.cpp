#include "Light.h"
#include "glm/gtc/type_ptr.hpp"
#include "../Graphics/Shader.h"
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
		color(Vector3(1.0f, 1.0f, 1.0f)), type(LightType::Environment)
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

		auto objs = scene->GetAllGameObjects();
		for (auto obj : objs)
		{
			auto renderList = obj->GetBaseComponents<Renderer>();
			for (auto render : renderList) if (render && render->GetShader())
			{
				//spdlog::info("{}({}) render {} call.", obj->name, obj->GetInstanceID(), typeid(render).name());				
				auto shader = render->GetShader();
				
				shader->SetFloat("intensity", intensity);
				shader->SetColor("lightColor", color);
				shader->SetVector3("lightPos", transform->position);

#ifdef NUWA_EDITOR
				shader->SetColor("gizmos.displayColor", Vector4(color, 1.0f));
#endif // NUWA_EDITOR
			}

		}
	}

	void Light::OnDisable()
	{
		auto objs = scene->GetAllGameObjects();
		for (auto obj : objs)
		{
			auto renderList = obj->GetBaseComponents<Renderer>();
			for (auto render : renderList) if (render && render->GetShader())
			{
				auto shader = render->GetShader();
				shader->SetFloat("intensity", 1.0f);
				shader->SetColor("lightColor", Vector3(1));
				shader->SetVector3("lightPos", Vector3(0));

#ifdef NUWA_EDITOR
				shader->SetColor("gizmos.displayColor", Vector4(1));
#endif // NUWA_EDITOR
			}
		}
	}

	void Light::OnInspectorGUI()
	{
#ifdef NUWA_EDITOR
		int val = (int)type;
		const char* items[] = { "Environment Light", "Direction Light", "Point Light" };
		EditorGUI::DrawCombo("Type", &val, items, 3);
		type = (LightType)val;

		switch (type)
		{
		case LightType::Environment:
			EditorGUI::DrawEditColor3("Color", color);
			EditorGUI::DrawSlideFloat("Intensity", intensity, 0, 10);
			break;
		case LightType::Direction:
			ImGui::Text("Not Implement.");
			break;
		case LightType::Point:
			ImGui::Text("Not Implement.");
			break;
		default:
			ImGui::Text("Not Implement.");
			break;
		}
#endif
	}


}