//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_DESKTOPLOGGER_H
#define AVALONENGINE_DESKTOPLOGGER_H


#include "Logger.h"

namespace av
{

    class DesktopLogger : public Logger
    {
    public:
        DesktopLogger() = default;
        void Log(std::string l_location, std::string l_message) override;
    };

}


#endif //AVALONENGINE_DESKTOPLOGGER_H
