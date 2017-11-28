#pragma once

#include "FileSystem.hpp"

namespace av
{

    class DesktopFileSystem : public FileSystem
    {
        public:
            DesktopFileSystem();
            av::fs::Configuration GetConfiguration() override;
            void SaveConfiguration(av::fs::Configuration& l_cfg) override;
    };

}