//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_NULLLOGGER_H
#define AVALONENGINE_NULLLOGGER_H


#include "Logger.h"

namespace av
{

    class NullLogger : public Logger
    {
    public:
        NullLogger();
        void Log(std::string l_location, std::string l_message) override;
    };

}


#endif //AVALONENGINE_NULLLOGGER_H
