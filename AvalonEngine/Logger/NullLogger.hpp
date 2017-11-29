#pragma once

#include "Logger.hpp"

namespace av
{

    class NullLogger : public Logger
    {
    public:
        NullLogger();
        void Log(std::string l_location, std::string l_message) override;
    };

}