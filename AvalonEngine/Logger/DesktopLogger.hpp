#pragma once

#include "Logger.hpp"

namespace av
{

    class DesktopLogger : public Logger
    {
    public:
        DesktopLogger();
        void Log(std::ostream& l_val) override;
    };

}