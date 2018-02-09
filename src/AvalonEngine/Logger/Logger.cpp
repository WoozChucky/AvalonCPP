//
// Created by Nuno Levezinho on 07/02/2018.
//

#include "Logger.h"

av::Logger::Logger(av::typelog l_type) {
    this->msg_level_ = l_type;
    operator << ("["+getLevel(this->msg_level_)+"]");
}

av::Logger::~Logger() {
    if(is_open_)
    {
        std::cout << std::endl;
    }
    is_open_ = false;
}

std::string av::Logger::getLevel(av::typelog l_type) {
    std::string label;
    switch (l_type) {
        case DEBUG: label = "DEBUG"; break;
        case INFO:  label = "INFO "; break;
        case WARN:  label = "WARN "; break;
        case ERROR: label = "ERROR"; break;
    }
    return label;
}
