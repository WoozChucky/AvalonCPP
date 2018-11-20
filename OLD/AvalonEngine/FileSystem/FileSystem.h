//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_FILESYSTEM_H
#define AVALONENGINE_FILESYSTEM_H

#include <string>
#include "File.h"

namespace av
{

    class FileSystem
    {
    public:
        virtual fs::Configuration GetConfiguration() = 0;
        virtual void SaveConfiguration(fs::Configuration& l_cfg) = 0;
    protected:
        std::string const kConfigurationLocation = "Assets/plattform.av";
    };

}

#endif //AVALONENGINE_FILESYSTEM_H
