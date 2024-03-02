#pragma once

#include "Application.h"

#ifdef AV_PLATFORM_WINDOWS

extern Avalon::Application* Avalon::CreateApplication();

int main(int argc, char** argv)
{
	Avalon::Log::Init();
	AV_PROFILE_BEGIN_SESSION("Startup", "AvalonProfile-Startup.json");
	auto app = Avalon::CreateApplication();
	AV_PROFILE_END_SESSION();

	AV_PROFILE_BEGIN_SESSION("Runtime", "AvalonProfile-Runtime.json");
	app->Run();
	AV_PROFILE_END_SESSION();

	AV_PROFILE_BEGIN_SESSION("Startup", "AvalonProfile-Shutdown.json");
	delete app;
	AV_PROFILE_END_SESSION();
}

#endif