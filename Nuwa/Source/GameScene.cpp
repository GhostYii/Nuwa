#include "GameScene.h"
#include "Basic/UUID.h"
#include "Component/Light.h"
#include "Graphics/FrameRenderElement.h"
#include "Global.h"

namespace Nuwa
{
	Camera* GameScene::mainCamera;

	GameScene::GameScene()
		: name("New Game Scene"), id(UUID::Generate()), objMap(std::unordered_map<uint64, GameObject*>())
	{
	}

	GameScene::GameScene(std::string name)
		: name(name), id(UUID::Generate()), objMap(std::unordered_map<uint64, GameObject*>())
	{
	}

	GameScene::~GameScene()
	{
		for (auto iter = objMap.begin(); iter != objMap.end(); iter++)
		{
			for (auto comIter = iter->second->components.begin(); comIter != iter->second->components.end(); comIter++)
			{
				if (dynamic_cast<BehaviorComponent*>(comIter->second))
				{
					BehaviorComponent* behavior = dynamic_cast<BehaviorComponent*>(comIter->second);
					behavior->Destory();
				}
			}
		}
	}

	void GameScene::AddGameObject(GameObject* gameObject)
	{
		if (objMap.find(gameObject->GetInstanceID()) != objMap.end())
			return;

		objMap[gameObject->GetInstanceID()] = gameObject;
		allObjs.push_back(gameObject);

		for (auto comIter = gameObject->components.begin(); comIter != gameObject->components.end(); comIter++)
		{
			if (dynamic_cast<BehaviorComponent*>(comIter->second))
			{
				BehaviorComponent* behavior = dynamic_cast<BehaviorComponent*>(comIter->second);
				behavior->Awake();
				behavior->InternalStart();
			}
		}

	}

	GameObject* GameScene::Find(const uint64 id)
	{
		if (objMap.find(id) != objMap.end())
			return objMap.find(id)->second;

		return nullptr;
	}

	GameObject* GameScene::Find(const std::string name)
	{
		for (auto iter : objMap)
		{
			if (iter.second->name == name)
				return iter.second;
		}

		return nullptr;
	}

	void GameScene::Update()
	{
		for (auto iter = objMap.begin(); iter != objMap.end(); iter++)
		{
			for (auto comIter = iter->second->components.begin(); comIter != iter->second->components.end(); comIter++)
			{
				if (dynamic_cast<BehaviorComponent*>(comIter->second))
				{
					BehaviorComponent* behavior = dynamic_cast<BehaviorComponent*>(comIter->second);
					behavior->InternalUpdate();
					behavior->InternalLateUpdate();
				}
			}
		}

	}

	void GameScene::Render()
	{
		for (auto iter = objMap.begin(); iter != objMap.end(); iter++)
		{
			for (auto comIter = iter->second->components.begin(); comIter != iter->second->components.end(); comIter++)
			{
				if (dynamic_cast<BehaviorComponent*>(comIter->second))
				{
					BehaviorComponent* behavior = dynamic_cast<BehaviorComponent*>(comIter->second);
					if (behavior->enable)
						behavior->InternalRender();
				}
			}
		}
	}

	std::vector<GameObject*> GameScene::GetAllGameObjects() const
	{
		return allObjs;
	}
}
