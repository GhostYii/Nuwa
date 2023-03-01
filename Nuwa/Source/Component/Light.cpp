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
		: intensity(1.0f), color(Vector3(1.0f, 1.0f, 1.0f)), type(LightType::Direction)
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
	}

	void Light::OnInspectorGUI()
	{
#ifdef NUWA_EDITOR		
		int val = (int)type;
		const char* items[] = { "Direction Light", "Point Light" };
		EditorGUI::DrawCombo("Type", &val, items, 2);
		type = (LightType)val;

		EditorGUI::DrawDragFloat("Intensity", intensity);
		EditorGUI::DrawEditColor3("Color", color);

		switch (type)
		{
		case Nuwa::LightType::Direction:
			gameObject->GetComponent<GizmosRenderer>()->GetMaterial()->SetAlbedoMap("Resources/Editor/Icon/light_direction.png");
			break;
		case Nuwa::LightType::Point:
			gameObject->GetComponent<GizmosRenderer>()->GetMaterial()->SetAlbedoMap("Resources/Editor/Icon/light_point.png");
			break;
		default:
			break;
		}
		//switch (type)
		//{
		//case LightType::Direction:
		//	EditorGUI::DrawDragFloat("Intensity", intensity);
		//	EditorGUI::DrawEditColor3("Color", color);
		//	break;
		//case LightType::Point:
		//	EditorGUI::DrawEditColor3("Color", color);
		//	break;
		//default:
		//	ImGui::Text("Not Implement.");
		//	break;
		//}
#endif
	}


}