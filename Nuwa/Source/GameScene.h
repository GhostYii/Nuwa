#pragma once
#include "GameObject.h"

#ifdef NUWA_EDITOR
#include "Editor/Inspector.h"
#include "Editor/Hierarchy.h"
#endif

namespace Nuwa
{
	class GameScene
	{
		friend class GameWindow;
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

		std::vector<GameObject*> GetAllGameObjects() const;

	private:		
		uint64 id;

		//std::vector<GameObject*> objs;
		std::unordered_map<uint64, GameObject*> objMap;

//#ifdef NUWA_EDITOR
//		void AddEditorGUI(Editor::EditorGUI* editorGUI);
//		std::vector<Editor::EditorGUI*> editorGUIs;
//
//		void OnEditorGUI();
//
//#endif // NUWA_EDITOR
	};
}