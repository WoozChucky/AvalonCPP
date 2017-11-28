#include "DesktopFileSystem.hpp"

av::DesktopFileSystem::DesktopFileSystem()
{
    
}

av::fs::Configuration av::DesktopFileSystem::GetConfiguration()
{
	fs::Configuration read_cfg;	

	std::ifstream input_file(this->kConfigurationLocation, std::ios::binary);
	input_file.read((char*)&read_cfg, sizeof(read_cfg));   
    input_file.close();

	return read_cfg;
}

void av::DesktopFileSystem::SaveConfiguration(av::fs::Configuration& l_cfg)
{
    std::ofstream output_file(this->kConfigurationLocation, std::ios::binary);
	output_file.write((char*)&l_cfg, sizeof(l_cfg));
	output_file.close();
}