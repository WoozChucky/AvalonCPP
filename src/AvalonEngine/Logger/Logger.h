//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_LOGGER_H
#define AVALONENGINE_LOGGER_H

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

#endif //AVALONENGINE_LOGGER_H
