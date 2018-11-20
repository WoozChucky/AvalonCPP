#pragma once
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <ctime>
#include <string>

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

		explicit Logger(typelog l_type)
		{
			this->msg_level_ = l_type;

			time_t rawtime;
			char time_buffer[80];

			time(&rawtime);
			const auto timeinfo = localtime(&rawtime);
			strftime(time_buffer, 80, "%T", timeinfo);

			operator << ("[" + getLevel(this->msg_level_) + "]" + time_buffer + ": ");
		}

		~Logger()
		{
			if (is_open_)
			{
				std::cout << std::endl;
			}
			is_open_ = false;
		}

		template<class T>
		Logger &operator<<(const T &l_msg) {

			std::cout << l_msg;
			is_open_ = true;

			return  *this;
		}

	private:
		bool is_open_ = false;
		typelog msg_level_ = DEBUG;

		std::string getLevel(const typelog l_type)
		{
			std::string label;
			switch (l_type) {
			case DEBUG: label = "DEBUG"; break;
			case INFO:  label = "INFO "; break;
			case WARN:  label = "WARN "; break;
			case ERROR: label = "ERROR"; break;
			}
			return label;
		}
	};

}