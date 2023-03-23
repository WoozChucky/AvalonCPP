//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_DESKTOPFILESYSTEM_H
#define AVALONENGINE_DESKTOPFILESYSTEM_H


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
        static bool FileExists(std::string filename);
        void GenerateDefaultConfiguration() const;

    };

}


#endif //AVALONENGINE_DESKTOPFILESYSTEM_H
