//
// Created by Nuno Levezinho on 07/02/2018.
//

#include "DesktopFileSystem.h"
#include <sys/stat.h>
#include <ios>
#include <fstream>

av::DesktopFileSystem::DesktopFileSystem() = default;

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
    struct stat file_info{};
    return stat(filename.c_str(), &file_info) == 0;
}

void av::DesktopFileSystem::GenerateDefaultConfiguration() const
{
    fs::Configuration default_cfg{};
    default_cfg.video_l.Width = 800;
    default_cfg.video_l.Height = 600;
    default_cfg.video_l.Bpp = 32;
    default_cfg.audio_l.SFX = 100;
    default_cfg.audio_l.Music = 100;

    std::ofstream output_file(this->kConfigurationLocation, std::ios::binary);
    output_file.write(reinterpret_cast<char*>(&default_cfg), sizeof(default_cfg));
    output_file.close();
}