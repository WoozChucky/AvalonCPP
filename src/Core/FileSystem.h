#pragma once

#include <string>
#include "File.h"

namespace av
{

	class FileSystem
	{
	public:
		virtual ~FileSystem() = default;
		virtual fs::Configuration GetConfiguration() = 0;
		virtual void SaveConfiguration(fs::Configuration& l_cfg) = 0;
	protected:
		std::string const kConfigurationLocation = "Assets/plattform.av";
	};

}