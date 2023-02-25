#pragma once
//#define MINI_CASE_SENSITIVE
#include <mINI/ini.h>

namespace Nuwa
{
	class INIConfig
	{
	public:
		INIConfig(const std::string& path);
		~INIConfig();

		mINI::INIMap<std::string>& operator[] (std::string key);

	private:
		mINI::INIFile file;
		mINI::INIStructure ini;
	};
}