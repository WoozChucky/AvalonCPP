#include "DesktopFileSystem.h"
#include <sys/stat.h>
#include <fstream>
#include <SFML/System.hpp>

using namespace av;

DesktopFileSystem::DesktopFileSystem() = default;

fs::Configuration DesktopFileSystem::GetConfiguration()
{
	fs::Configuration read_cfg = {};

	std::ifstream input_file(this->kConfigurationLocation, std::ios::binary);
	
	if (FileExists(this->kConfigurationLocation))
	{
		input_file.read(reinterpret_cast<char*>(&read_cfg), sizeof(read_cfg));
		input_file.close();
	}
	else
	{
		this->GenerateDefaultConfiguration();
		return this->GetConfiguration();
	}

	return read_cfg;
}

void DesktopFileSystem::SaveConfiguration(fs::Configuration& l_cfg)
{
	std::ofstream output_file(this->kConfigurationLocation, std::ios::binary);
	output_file.write(reinterpret_cast<char*>(&l_cfg), sizeof(l_cfg));
	output_file.close();
}

bool DesktopFileSystem::FileExists(const std::string& filename)
{
	struct stat file_info {};
	return stat(filename.c_str(), &file_info) == 0;
}

void DesktopFileSystem::GenerateDefaultConfiguration() const
{
	fs::Configuration default_cfg 
	{ 
		{ 800, 600, 32 },	// Video Settings
		{ 100, 100 }		// Audio Settings
	};

	std::ofstream output_file(this->kConfigurationLocation, std::ios::binary);
	output_file.write(reinterpret_cast<char*>(&default_cfg), sizeof(default_cfg));
	output_file.close();
}