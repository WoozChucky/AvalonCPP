#pragma once

#include <memory>
#include <GL/glew.h>
#include <imgui.h>
#include <SDL.h>
#include "NetworkDaemon.h"
#include "Engine/Graphics/Raw/Texture.h"
#include "Engine/Graphics/Camera2D.h"
#include "Engine/Graphics/SpriteBatch.h"
#include "Engine/Graphics/Projectile.h"
#include "Engine/Graphics/ProjectileRenderer.h"
#include "Engine/Graphics/EntityRenderer.h"
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

    U64 _frameDelay = 1000 / _settings.Video.TargetFramesPerSecond;
    U64 _frameStart = 0;

    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    F32 _shaderTime = 0.0f;
    GameSettings _settings;
    ResolutionOption _currentResolution = RESOLUTION_1280x720;
    FPSOption _currentFPS = FPS_60;
    bool _debugWindow = false;
    bool _transitionToDebug = false;

    void HandleEvents(F32 deltaTime);
    void Update(F32 deltaTime);
    void Render();
};
