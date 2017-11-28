#include "DesktopFileSystem.hpp"
#include <sys/stat.h>

av::DesktopFileSystem::DesktopFileSystem()
{
    
}

av::fs::Configuration av::DesktopFileSystem::GetConfiguration()
{
	fs::Configuration read_cfg = {0};	

	std::ifstream input_file(this->kConfigurationLocation, std::ios::binary);
	if(this->FileExists(this->kConfigurationLocation))
	{
		input_file.read(reinterpret_cast<char*>(&read_cfg), sizeof(read_cfg));
		input_file.close();
	}
	else
	{
		this->GenerateDefaultConfiguration();
		return GetConfiguration();
	}

	return read_cfg;
}

void av::DesktopFileSystem::SaveConfiguration(fs::Configuration& l_cfg)
{
    std::ofstream output_file(this->kConfigurationLocation, std::ios::binary);
	output_file.write(reinterpret_cast<char*>(&l_cfg), sizeof(l_cfg));
	output_file.close();
}

bool av::DesktopFileSystem::FileExists(std::string filename)
{
	struct stat file_info;
	return stat(filename.c_str(), &file_info) == 0;
}

void av::DesktopFileSystem::GenerateDefaultConfiguration() const
{
	fs::Configuration default_cfg;
	default_cfg.Video.Width = 800;
	default_cfg.Video.Height = 600;
	default_cfg.Video.Bpp = 32;
	default_cfg.Audio.SFX = 100;
	default_cfg.Audio.Music = 100;

	std::ofstream output_file(this->kConfigurationLocation, std::ios::binary);
	output_file.write(reinterpret_cast<char*>(&default_cfg), sizeof(default_cfg));
	output_file.close();
}
