#pragma once
#include "../GUI.h"
#include "../EngineTypes.h"
#include "../Basic/UUID.h"

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
		};
	}
}
