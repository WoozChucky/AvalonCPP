#pragma once

#include "File.h"
#include "FileSystem.h"

namespace av
{

	class DesktopFileSystem : public FileSystem
	{
	public:
		DesktopFileSystem();
		fs::Configuration GetConfiguration() override;
		void SaveConfiguration(fs::Configuration& l_cfg) override;
	private:
		static bool FileExists(const std::string& filename);
		void GenerateDefaultConfiguration() const;

	};

}


