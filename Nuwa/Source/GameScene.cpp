#include "GameScene.h"
#include "Basic/UUID.h"
#include "Component/BehaviorComponent.h"

namespace Nuwa
{
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

		for (auto iter = objMap.begin(); iter != objMap.end(); iter++)
		{
			for (auto comIter = iter->second->components.begin(); comIter != iter->second->components.end(); comIter++)
			{
				if (dynamic_cast<BehaviorComponent*>(comIter->second))
				{
					BehaviorComponent* behavior = dynamic_cast<BehaviorComponent*>(comIter->second);
					behavior->Awake();
					behavior->InternalStart();
				}
			}
		}
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
					behavior->InternalRender();
				}
			}
		}

	}
}
