#pragma once
#include "../GUI.h"
#include "../EngineTypes.h"
#include "../Basic/UUID.h"

namespace Nuwa
{
	namespace Editor
	{
#define EDITOR_DEFAULT_TITLE_WIDTH 100
	}
}

namespace Nuwa
{
	namespace Editor
	{
		class EditorGUI
		{
			friend class EditorMode;
		public:
			EditorGUI();
			virtual ~EditorGUI();

			bool isOpen;

		protected:
			uint64 id;
			std::string title;

			//inline void BeginGUI() { Nuwa::BeginImGui(); }
			//inline void RenderGUI() { OnGUI(); }
			//inline void EndGUI() { Nuwa::EndImGui(); }

			virtual void Start() {}
			virtual void OnGUI() {}
			virtual void Destory() {}

		private:
			void RenderGUI();


		public:
			static void DrawDragFloat(std::string name, float& value);
			static void DrawSlideFloat(std::string name, float& value, float min, float max);
			static void DrawDragInt(std::string name, int& value);
			static void DrawSlideInt(std::string name, int& value, int min, int max);

			static void DrawDragVector2(std::string name, Vector2& value);
			static void DrawDragVector3(std::string name, Vector3& value);

			static void DrawLabel(std::string name, std::string value);
			static void DrawText(std::string name, char* buf, size_t buf_size = 1024);

		};
	}
}
