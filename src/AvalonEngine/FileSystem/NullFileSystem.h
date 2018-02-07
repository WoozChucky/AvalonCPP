//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_NULLFILESYSTEM_H
#define AVALONENGINE_NULLFILESYSTEM_H

#include "FileSystem.h"

namespace av
{

    class NullFileSystem : public FileSystem
    {
    public:
        NullFileSystem();
        av::fs::Configuration GetConfiguration() override;
        void SaveConfiguration(av::fs::Configuration& l_cfg) override;
    };

}

#endif //AVALONENGINE_NULLFILESYSTEM_H
