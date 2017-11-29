#pragma once

#include <iostream>

namespace av
{

    class Logger
    {
    public:
        virtual void Log(std::ostream& l_val) = 0;
    };

}