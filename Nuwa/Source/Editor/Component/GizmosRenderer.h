#pragma once
#ifdef NUWA_EDITOR

#include "../../Component/Renderer.h"

namespace Nuwa
{
	namespace Editor
	{		
		class GizmosRenderer : public Renderer
		{
		public:
			GizmosRenderer(std::string iconPath);
			~GizmosRenderer();

		private:
			std::string path;
		};
	}

}
#endif // NUWA_EDITOR