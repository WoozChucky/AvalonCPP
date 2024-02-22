#pragma once

#include <memory>
#include <GL/glew.h>
#include <imgui.h>
#include <SDL.h>
#include "NetworkDaemon.h"

#include <Engine/Settings.h>

using namespace Avalon::Engine;

class Game {
public:
    Game(boost::asio::io_context &ioContext, GameSettings &settings);
    ~Game();
    void Run();
    void Stop();
    void Shutdown();

private:
    bool _isRunning;
    boost::asio::io_context &ioContext;
    std::unique_ptr<NetworkDaemon> _networkDaemon;
    SDL_Window* _window;
    SDL_GLContext _glContext;
    ImGuiIO& _io;

    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.15f, 0.15, 0.15, 1.00f);

    GameSettings _settings;
    ResolutionOption _currentResolution = RESOLUTION_1280x720;
    bool _debugWindow = false;
    bool _transitionToDebug = false;

    void HandleEvents(F32 deltaTime);
    void Update(F32 deltaTime);
    void Render();
};
