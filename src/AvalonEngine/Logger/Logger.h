//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_DESKTOPLOGGER_H
#define AVALONENGINE_DESKTOPLOGGER_H

#include <iostream>

namespace av
{

    enum typelog {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    class Logger
    {
    public:
        Logger() = default;
        explicit Logger(typelog l_type);
        ~Logger();

        template<class T>
        Logger &operator<<(const T &l_msg) {

            std::cout << l_msg;
            is_open_ = true;

            return  *this;
        }

    private:
        bool is_open_ = false;
        typelog msg_level_ = DEBUG;
        std::string getLevel(typelog l_type);
    };

}


#endif //AVALONENGINE_DESKTOPLOGGER_H
