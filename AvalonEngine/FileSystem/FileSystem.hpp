#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "File.hpp"

namespace av
{

    class FileSystem
    {
        public:
            virtual fs::Configuration GetConfiguration() = 0;
            void virtual SaveConfiguration(fs::Configuration& l_cfg) = 0;
        protected:
            std::string kConfigurationLocation = "Assets/plattform.av";
    };

}