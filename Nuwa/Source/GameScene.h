#pragma once
#include "GameObject.h"

namespace Nuwa
{
	class GameScene
	{
	public:
		GameScene();
		GameScene(std::string name);
		virtual ~GameScene();

		std::string name;

		void AddGameObject(GameObject* gameObject);

		//void RemoveGameObject(const GameObject* gameObject);
		//void RemoveGameObject(const uint64 gameObjectID);

		//GameObject* Find(const std::string name);
		//std::vector<GameObject*> FindAll(const std::string name);

		//void Save();	
		
		void Update();
		void Render();

	private:		
		uint64 id;

		//std::vector<GameObject*> objs;
		std::unordered_map<uint64, GameObject*> objMap;
	};
}