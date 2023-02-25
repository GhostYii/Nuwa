#include "INIConfig.h"

namespace Nuwa
{
	INIConfig::INIConfig(const std::string& path)
		: file(path), ini(mINI::INIStructure())
	{
		file.read(ini);
	}

	INIConfig::~INIConfig()
	{		
	}

	mINI::INIMap<std::string>& INIConfig::operator[](std::string key)
	{
		return ini[key];
	}
}