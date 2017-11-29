#pragma once

#include "Logger.hpp"

namespace av
{

    class NullLogger : public Logger
    {
    public:
        NullLogger();
        void Log(std::ostream& l_val) override;
    };

}