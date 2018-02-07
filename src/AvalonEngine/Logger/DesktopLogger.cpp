//
// Created by Nuno Levezinho on 07/02/2018.
//

#include "DesktopLogger.h"

void av::DesktopLogger::Log(std::string l_location, std::string l_message)
{
    time_t rawtime;
    char time_buffer[80];

    time(&rawtime);
    const auto timeinfo = localtime(&rawtime);
    strftime(time_buffer, 80, "%T", timeinfo);

    std::cout << "[LOGGER] " << time_buffer << " - " << l_location.c_str() << "\n\t" << l_message.c_str() << std::endl;
}