#pragma once

#include <memory>
#include <GL/glew.h>
#include <imgui.h>
#include <SDL.h>
#include "NetworkDaemon.h"
#include "Engine/Graphics/Raw/Texture.h"
#include <Engine/Graphics/Raw/Sprite.h>
#include <Engine/Graphics/Raw/Shader.h>
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

    U32 _frameDelay = 1000 / _settings.Video.TargetFramesPerSecond;
    U32 _frameStart = 0;

    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    std::vector<Sprite*> _sprites;
    Shader _shader;
    F32 _shaderTime = 0.0f;
    GameSettings _settings;
    ResolutionOption _currentResolution = RESOLUTION_1280x720;
    FPSOption _currentFPS = FPS_60;

    void HandleEvents();
    void Update();
    void Render();
};
