#pragma once
#ifdef NUWA_EDITOR

#include "../GUI.h"
#include "../EngineTypes.h"
#include "../Basic/UUID.h"

namespace Nuwa
{
	namespace Editor
	{
#define EDITOR_DEFAULT_TITLE_WIDTH 100
#define EDITOR_DEFAULT_DRAG_WIDTH 60
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
			virtual void OnGizmos() {}
			virtual void Destory() {}

		private:
			void RenderGUI();

		public:
			static void DrawDragFloat(std::string name, float& value);
			static void DrawSlideFloat(std::string name, float& value, float min, float max);
			static void DrawDragInt(std::string name, int& value);
			static void DrawSlideInt(std::string name, int& value, int min, int max);

			//static void DrawDragVector2(std::string name, Vector2& value);
			static void DrawDragVector3(std::string name, Vector3& value);

			static void DrawSingleText(const char* fmt, ...);
			static void DrawLabel(std::string name, std::string value);
			static void DrawInputText(std::string name, char* buf, size_t bufSize = 1024);

			static void DrawCombo(std::string name, int* currentItem, const char* const items[], int itemsCount);

			static void DrawEditColor3(std::string name, Vector3& color);
			static void DrawPickColor3(std::string name, Vector3& color);

			static void DrawToggle(std::string name, bool& isOn);

		};
	}
}

#endif // NUWA_EDITOR

