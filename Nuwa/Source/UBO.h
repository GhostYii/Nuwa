#pragma once
#include "Graphics/UniformBuffer.h"

namespace Nuwa
{
	class UBO
	{
	public:
		static std::unique_ptr<UniformBuffer> CameraMatrix;

	private:
		UBO() = default;
		~UBO() = default;
	};

	std::unique_ptr<UniformBuffer> UBO::CameraMatrix;
}