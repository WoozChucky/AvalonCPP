#include "Game.h"
#include <fmt/core.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif
#include <Engine/Audio/AudioManager.h>


#include "Common/Logging/Log.h"

Game::Game(boost::asio::io_context &ioContext): ioContext(ioContext), _io(ImGui::GetIO()){
    // Initialization code here
    _isRunning = false;
    _networkDaemon = std::make_unique<NetworkDaemon>();
    _networkDaemon->RegisterHandlers();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) < 0) {
        // Handle initialization error
        throw std::runtime_error("SDL_Init failed");
    }

    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

    // Create a window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL  | SDL_WINDOW_ALLOW_HIGHDPI);

    _window = SDL_CreateWindow(
            "SDL Game Loop",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            window_flags
    );

    if (!_window) {
        throw std::runtime_error("SDL_CreateWindow failed");
    }

    _glContext = SDL_GL_CreateContext(_window);
    if (!_glContext) {
        // Handle context creation error
        throw std::runtime_error("SDL_GL_CreateContext failed");
    }

    SDL_GL_MakeCurrent(_window, _glContext);

    // Setup Dear ImGui context
    ImGui::CreateContext();
    _io = ImGui::GetIO(); (void)_io;
    _io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    _io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    _io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;               // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(_window, _glContext);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Initialize GLEW
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        const unsigned char * err = glewGetErrorString(glewError);
        throw std::runtime_error(fmt::format("GLEW initialization failed: {}", reinterpret_cast<const char*>(err)));
    }

    sAudio->Initialize();

    LOG_INFO("game", "Game initialized");
}

Game::~Game() {
    sAudio->Shutdown();
}

void Game::Run() {

    _isRunning = true;

    sAudio->RecordAudio(10, []() {
        LOG_INFO("audio", "Finished recording");
    });

    while (_isRunning) {

        _frameStart = SDL_GetTicks();

        HandleEvents();
        Update();
        Render();

        // Calculate frame time
        auto frameTime = SDL_GetTicks() - _frameStart;

        // Cap frame rate
        if (_frameDelay > frameTime) {
            SDL_Delay(_frameDelay - frameTime);
        }

        // Update window title with frame time
        SDL_SetWindowTitle(_window, fmt::format("SDL Game Loop - {:.1f} ms/frame ({:.1f} FPS)", 1000.0f / _io.Framerate, _io.Framerate).c_str());
    }

}

void Game::Stop() {
    _isRunning = false;
}

void Game::Shutdown() {
    // Cleanup code here
    LOG_INFO("game", "Game shutting down");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // Clean up
    SDL_GL_DeleteContext(_glContext);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Game::HandleEvents() {
    // Event handling
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            _isRunning = false;
        if (event.type == SDL_WINDOWEVENT
            && event.window.event == SDL_WINDOWEVENT_CLOSE
            && event.window.windowID == SDL_GetWindowID(_window)) {
            _isRunning = false;
        }
    }
}

void Game::Update() {
    // Game logic update code here
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        if (ImGui::Button("Connect")) {
            _networkDaemon->Start(ioContext);
            SDL_SetWindowSize(_window, 1360, 768);
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / _io.Framerate, _io.Framerate);

        if (ImGui::Button("Quit")) {
            _isRunning = false;
        }
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
}

void Game::Render() {
    // Rendering code here
    // TODO: Render game elements
    ImGui::Render();

    // Clear the screen
    glViewport(0, 0, (int)_io.DisplaySize.x, (int)_io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // Swap buffers
    SDL_GL_SwapWindow(_window);
}



