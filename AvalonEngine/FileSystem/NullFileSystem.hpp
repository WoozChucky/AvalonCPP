#pragma once

#include "FileSystem.hpp"

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