#pragma once

#include <iostream>

namespace av
{

    class Logger
    {
    public:
	    virtual ~Logger() = default;
	    virtual void Log(std::string l_location, std::string l_message) = 0;
    };

}