//
// Created by nunol on 2/3/2024.
//

#ifndef AVALONGAME_GAME_H
#define AVALONGAME_GAME_H

#include <memory>
#include <GL/glew.h>
#include <imgui.h>
#include <SDL.h>
#include "NetworkDaemon.h"
#include <Engine/Graphics/Raw/Sprite.h>
#include <Engine/Graphics/Raw/Shader.h>


class Game {
public:
    Game(boost::asio::io_context &ioContext);
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

    U32 _desiredFPS = 60;
    U32 _frameDelay = 1000 / _desiredFPS;
    U32 _frameStart = 0;

    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    Sprite _sprite;
    Shader _shader;

    void HandleEvents();
    void Update();
    void Render();
};


#endif //AVALONGAME_GAME_H
