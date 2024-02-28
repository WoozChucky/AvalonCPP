#pragma once

#include "Application.h"

#ifdef AV_PLATFORM_WINDOWS

extern Avalon::Application* Avalon::CreateApplication();

int main(int argc, char** argv)
{
	Avalon::Log::Init();
	AV_CORE_WARN("Initialized Log!");
	int time = 10;
	AV_INFO("Hello! Var={0}", time);

	const auto app = Avalon::CreateApplication();
	app->Run();
	delete app;
}

#endif