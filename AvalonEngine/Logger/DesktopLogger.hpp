#pragma once

#include "Logger.hpp"

namespace av
{

    class DesktopLogger : public Logger
    {
    public:
        DesktopLogger();
        void Log(std::string l_location, std::string l_message) override;
    };

}