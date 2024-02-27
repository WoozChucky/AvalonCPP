#pragma once

#include "Application.h"

#ifdef AV_PLATFORM_WINDOWS

extern Avalon::Application* Avalon::CreateApplication();

inline int main(int argc, char** argv)
{
	printf("Avalon Engine\n");
	const auto app = Avalon::CreateApplication();
	app->Run();
	delete app;
}

#endif