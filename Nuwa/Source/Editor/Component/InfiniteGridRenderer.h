#pragma once
#ifdef NUWA_EDITOR

# include "../../Component/Renderer.h"

namespace Nuwa
{
	namespace Editor
	{		
		class InfiniteGridRenderer : public Renderer
		{
		public:
			InfiniteGridRenderer();
			virtual ~InfiniteGridRenderer();

		//protected:
		//	virtual void InternalRender() override;
		
		};
	}
}

#endif // NUWA_EDITOR

