#include "ToyMaterial.h"

namespace Nuwa
{
	bool ToyMaterial::HasShader() const
	{
		return shader != nullptr;
	}
}