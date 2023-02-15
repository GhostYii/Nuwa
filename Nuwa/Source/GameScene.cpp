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
					behavior->InternalRender();
				}
			}
		}

	}

	std::vector<GameObject*> GameScene::GetAllGameObjects() const
	{
		auto res = std::vector<GameObject*>();

		for (auto iter : objMap)		
			res.push_back(iter.second);		

		return res;
	}

//#ifdef NUWA_EDITOR
//	void GameScene::AddEditorGUI(Editor::EditorGUI* editorGUI)
//	{
//		if (!editorGUI)
//			return;
//
//		// 编辑器性能优化？
//		if (std::find(editorGUIs.begin(), editorGUIs.end(), editorGUI) != editorGUIs.end())
//			return;
//
//		editorGUI->Start();
//		editorGUIs.push_back(editorGUI);
//	}
//
//	void GameScene::OnEditorGUI()
//	{
//		for (auto iter : editorGUIs)
//			iter->RenderGUI();
//	}
//
//#endif // NUWA_EDITOR
}
