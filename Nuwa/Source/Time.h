#pragma once
#include <string>

namespace Nuwa
{
	class Time
	{
	public:
		static float GetTime();
		static std::string GetLocalTimeStr();

		static float deltaTime;

	private:
		Time() = default;
		~Time() = default;
	};
}