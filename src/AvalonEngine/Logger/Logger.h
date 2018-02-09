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
        explicit DesktopLogger(typelog l_type);
        ~DesktopLogger() override;

        template<class T>
        DesktopLogger &operator<<(const T &l_msg) {
            if(msg_level_ >= LOGCFG.level) {
                std::cout << l_msg;
                is_open_ = true;
            }
            return  *this;
        }

    private:
        std::string getLevel(typelog l_type) override;
    };

}


#endif //AVALONENGINE_DESKTOPLOGGER_H
