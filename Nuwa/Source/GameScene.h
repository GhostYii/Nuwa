#pragma once
#include "GameObject.h"
#include "Skybox.h"

#ifdef NUWA_EDITOR
#include "Editor/EditorViewTypes.h"
#endif

namespace Nuwa
{
	class Light;
	class Camera;
	class FrameRenderElement;

	class GameScene
	{		
		friend class GameWindow;
	public:
		GameScene();
		GameScene(std::string name);
		virtual ~GameScene();

		std::string name;

		void AddGameObject(GameObject* gameObject);

		GameObject* Find(const uint64 id);
		GameObject* Find(const std::string name);
		//std::vector<GameObject*> FindAll(const std::string name);

		//void RemoveGameObject(const GameObject* gameObject);
		//void RemoveGameObject(const uint64 gameObjectID);		

		//void Save();	
		
		void Update();
		void Render();

		std::vector<GameObject*> GetAllGameObjects() const;
		
	private:		
		uint64 id;

		std::vector<GameObject*> allObjs;
		std::unordered_map<uint64, GameObject*> objMap;

	public:
		static Camera* mainCamera;

		static void CreateSkybox(const std::string filename = "Default");

	private:
		static Skybox* skybox;		
	};
}