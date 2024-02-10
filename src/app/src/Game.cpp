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
#include "Engine/Graphics/AssetManager.h"
#include "Engine/Input/InputManager.h"

void OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
        LOG_WARN("graphics", "OpenGL Debug Message: {}", message);
    }
}

Game::Game(boost::asio::io_context &ioContext, GameSettings &settings): ioContext(ioContext), _io(ImGui::GetIO()){
    // Initialization code here
    _settings = settings;
    _isRunning = false;
    _networkDaemon = std::make_unique<NetworkDaemon>();
    _networkDaemon->RegisterHandlers();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) < 0) {
        // Handle initialization error
        throw std::runtime_error("SDL_Init failed");
    }

    const char* glsl_version = "#version 410";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

    // Create a window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    _window = SDL_CreateWindow(
            "SDL Game Loop",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            (S32) _settings.Video.Resolution.Width,
            (S32) _settings.Video.Resolution.Height,
            _settings.Video.Mode
    );

    if (!_window) {
        throw std::runtime_error("SDL_CreateWindow failed");
    }

    _currentResolution = _settings.Video.Resolution.GetResolutionOption();

    _glContext = SDL_GL_CreateContext(_window);
    if (!_glContext) {
        // Handle context creation error
        LOG_ERROR("graphics", "SDL_GL_CreateContext failed. {}", SDL_GetError());
        throw std::runtime_error("SDL_GL_CreateContext failed");
    }

    SDL_GL_MakeCurrent(_window, _glContext);

    glClearDepth(1.0f);

    // Setup Dear ImGui context
    ImGui::CreateContext();
    _io = ImGui::GetIO(); (void)_io;
    _io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    _io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    _io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(_window, _glContext);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        const unsigned char * err = glewGetErrorString(glewError);
        throw std::runtime_error(fmt::format("GLEW initialization failed: {}", reinterpret_cast<const char*>(err)));
    }

    std::string str(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    LOG_DEBUG("system", "> Using OpenGL version: {}", str.c_str());

    if (glewIsSupported("GL_KHR_debug")) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLDebugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    } else if (glewIsSupported("GL_ARB_debug_output")) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
        glDebugMessageCallbackARB(OpenGLDebugCallback, nullptr);
        glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    SDL_GL_SetSwapInterval(_settings.Video.VSync ? 1 : 0);
    LOG_INFO("graphics", "VSync: {}", _settings.Video.VSync ? "Enabled" : "Disabled");

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    sAudio->Initialize(_settings.Audio, [this](U8 *stream, int len) {
        // Audio recorded callback
        auto audioData = std::vector<U8>(stream, stream + len);
        _networkDaemon->SendAudioPacket(audioData);
    });

    _camera.Init(_settings.Video.Resolution.Width, _settings.Video.Resolution.Height);

    //_sprites.push_back(new Sprite());
    //_sprites[0]->Init(0.0f, 0.0f, 50.0f, 50.f, TexturesName::Player);

    _shader.Init("shaders/colorShading.vert", "shaders/colorShading.frag");
    _shader.AddAttribute("position");
    _shader.AddAttribute("color");
    _shader.AddAttribute("textCoord");
    _shader.Link();

    _spriteBatch.Initialize();

    LOG_INFO("game", "Game initialized");
}

Game::~Game() {
    sAudio->Shutdown();
    sAssetManager->Shutdown();
}

void Game::Run() {

    _isRunning = true;

    while (_isRunning) {

        _frameDelay = 1000 / _settings.Video.TargetFramesPerSecond;

        _frameStart = SDL_GetTicks64();

        HandleEvents();
        Update();
        Render();

        // Calculate frame time
        auto frameTime = SDL_GetTicks64() - _frameStart;

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

    if (SaveGameSettings(_settings, DEFAULT_GAME_SETTINGS_PATH)) {
        LOG_DEBUG("engine", "Saved game settings to '{}'", DEFAULT_GAME_SETTINGS_PATH);
    } else {
        LOG_ERROR("engine", "Failed to save game settings");
    }

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
        switch (event.type) {
            case SDL_QUIT:
                _isRunning = false;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE
                && event.window.windowID == SDL_GetWindowID(_window)) {
                    _isRunning = false;
                }
                break;
            case SDL_KEYUP:
                sInputManager->ReleaseKey(event.key.keysym.sym);
                break;
            case SDL_KEYDOWN:
                sInputManager->PressKey(event.key.keysym.sym);
                break;
        }
    }

    if (sInputManager->IsKeyDown(SDLK_w)) {
        _camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, 10.0f));
    }
    if (sInputManager->IsKeyDown(SDLK_s)) {
        _camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, -10.0f));
    }
    if (sInputManager->IsKeyDown(SDLK_a)) {
        _camera.SetPosition(_camera.GetPosition() + glm::vec2(-10.0f, 0.0f));
    }
    if (sInputManager->IsKeyDown(SDLK_d)) {
        _camera.SetPosition(_camera.GetPosition() + glm::vec2(10.0f, 0.0f));
    }
    if (sInputManager->IsKeyDown(SDLK_q)) {
        _camera.SetScale(_camera.GetScale() + 0.1f);
    }
    if (sInputManager->IsKeyDown(SDLK_e)) {
        _camera.SetScale(_camera.GetScale() - 0.1f);
    }
    if (sInputManager->IsKeyDown(SDLK_ESCAPE)) {
        _isRunning = false;
    }
}

void Game::Update() {
    // Game logic update code here
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }


    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Avalon Debugging");

        //ImGui::CollapsingHeader("Graphics");
        ImGui::NewLine();
        ImGui::SeparatorText("Graphics");
        ImGui::NewLine();
        ImGui::Text("Resolution: %d x %d", _settings.Video.Resolution.Width, _settings.Video.Resolution.Height);
        static int resOption = _currentResolution;
        ImGui::RadioButton("1280 × 720", &resOption, 0); ImGui::SameLine();
        ImGui::RadioButton("1920 x 1080", &resOption, 1); ImGui::SameLine();
        ImGui::RadioButton("2560 x 1440", &resOption, 2);
        if (_currentResolution != (ResolutionOption)resOption) {
            _currentResolution = (ResolutionOption)resOption;
            switch (_currentResolution) {
                case RESOLUTION_1280x720:
                    _settings.Video.Resolution.Width = 1280;
                    _settings.Video.Resolution.Height = 720;
                    break;
                case RESOLUTION_1920x1080:
                    _settings.Video.Resolution.Width = 1920;
                    _settings.Video.Resolution.Height = 1080;
                    break;
                case RESOLUTION_2560x1440:
                    _settings.Video.Resolution.Width = 2560;
                    _settings.Video.Resolution.Height = 1440;
                    break;
            }
            SDL_SetWindowSize(_window, _settings.Video.Resolution.Width, _settings.Video.Resolution.Height);
            SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        }

        ImGui::Text("Mode: %s",
                    _settings.Video.Mode == VideoMode::Windowed ? "Windowed"
                    : _settings.Video.Mode == VideoMode::Borderless ? "Borderless"
                    : _settings.Video.Mode == VideoMode::Fullscreen ? "Fullscreen" : "Fullscreen Borderless"
        );
        static int modeOption = _settings.Video.Mode;
        ImGui::RadioButton("Windowed", &modeOption, VideoMode::Windowed); ImGui::SameLine();
        ImGui::RadioButton("Borderless", &modeOption, VideoMode::Borderless); ImGui::SameLine();
        ImGui::RadioButton("Fullscreen", &modeOption, VideoMode::Fullscreen); ImGui::SameLine();
        ImGui::RadioButton("Fullscreen Borderless", &modeOption, VideoMode::FullscreenBorderless);
        //if (_settings.Video.Mode != (VideoMode)modeOption) {
        //    _settings.Video.Mode = (VideoMode)modeOption;
        //    SDL_SetWindowFullscreen(_window, _settings.Video.Mode);
        //}

        ImGui::Text("FPS %.1f (%.3f ms/frame)", _io.Framerate, 1000.0f / _io.Framerate);
        static int fpsOption = _settings.Video.TargetFramesPerSecond;
        ImGui::RadioButton("30FPS", &fpsOption, 30); ImGui::SameLine();
        ImGui::RadioButton("60FPS", &fpsOption, 60); ImGui::SameLine();
        ImGui::RadioButton("120FPS", &fpsOption, 120); ImGui::SameLine();
        ImGui::RadioButton("144FPS", &fpsOption, 144); ImGui::SameLine();
        ImGui::RadioButton("240FPS", &fpsOption, 240); ImGui::SameLine();
        ImGui::RadioButton("360FPS", &fpsOption, 360);
        if (_settings.Video.TargetFramesPerSecond != (FPSOption)fpsOption) {
            _settings.Video.TargetFramesPerSecond = (FPSOption)fpsOption;
        }

        //ImGui::CollapsingHeader("Audio");
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::SeparatorText("Audio");
        ImGui::NewLine();
        if (ImGui::BeginCombo("Input Device", sAudio->GetInputDeviceName().empty() ? "Select an input device" : sAudio->GetInputDeviceName().c_str()))
        {
            for (auto& device : sAudio->GetInputDevices()) {
                bool isSelected = (device == sAudio->GetInputDeviceName());
                if (ImGui::Selectable(device.c_str(), isSelected)) {
                    sAudio->Shutdown();
                    _settings.Audio.InputDevice = device;
                    sAudio->Initialize(_settings.Audio);
                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        ImGui::SliderInt("Input Volume", &_settings.Audio.InputVolume, 0, 100);
        if (ImGui::BeginCombo("Output Device", sAudio->GetOutputDeviceName().empty() ? "Select an output device" : sAudio->GetOutputDeviceName().c_str()))
        {
            for (auto& device : sAudio->GetOutputDevices()) {
                bool isSelected = (device == sAudio->GetOutputDeviceName());
                if (ImGui::Selectable(device.c_str(), isSelected)) {
                    sAudio->Shutdown();
                    _settings.Audio.OutputDevice = device;
                    sAudio->Initialize(_settings.Audio);
                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        ImGui::SliderInt("Output Volume", &_settings.Audio.OutputVolume, 0, 100);

        static bool muteAudio = false;
        ImGui::Checkbox("Audio", &muteAudio);
        if (!muteAudio) {
            _settings.Audio.OutputVolume = 100;
        } else {
            _settings.Audio.OutputVolume = 0;
        }
        ImGui::SameLine();
        static bool muteMic = true;
        ImGui::Checkbox("Microphone", &muteMic);
        if (!muteMic) {
            sAudio->RecordAudio();
        } else {
            sAudio->StopRecording();
        }


        ImGui::NewLine();
        ImGui::NewLine();

        //ImGui::CollapsingHeader("Network");
        ImGui::SeparatorText("Network");
        if (ImGui::Button("Connect")) {
            _networkDaemon->Start(ioContext);
        }
        ImGui::SameLine();
        ImGui::Text("Status: %s", _networkDaemon->IsConnected() ? "Connected" : "Disconnected");
        static char username[32] = "";
        ImGui::InputText("Username", username, IM_ARRAYSIZE(username));
        static char password[32] = "";
        ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);
        if (ImGui::Button("Login")) {
            _networkDaemon->Login(username, password);
        }
        ImGui::SameLine();
        ImGui::Text("Logged: %s", _networkDaemon->IsLogged() ? "Yes" : "No");
        //ImGui::PlotLines("Ping", _networkDaemon->GetPing().data(), _networkDaemon->GetPing().size(), 0, "ms", 0, 100, ImVec2(0, 80));


        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();

        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        //ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::ColorEdit3("background test", (float*)&clear_color); // Edit 3 floats representing a color

        ImGui::Separator();
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

    _camera.Update();
}

void Game::Render() {
    // 1. Clear the screen
    glViewport(0, 0, (int)_io.DisplaySize.x, (int)_io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    {
        _shaderTime += 0.05f;

        _shader.Bind();

        glActiveTexture(GL_TEXTURE0);

        auto textureLocation = _shader.GetUniformLocation("spriteTexture");
        glUniform1i(textureLocation, 0);

        //auto timeLocation = _shader.GetUniformLocation("time");
        //glUniform1f(timeLocation, _shaderTime);

        auto projectionLocation = _shader.GetUniformLocation("projection");
        glm::mat4 cameraMatrix = _camera.GetCameraMatrix();
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

        _spriteBatch.Begin();

        static Color color;
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 255;

        static U32 textureId =  sAssetManager->GetTexture(TexturesName::Player).Id;

        for (int i = 0; i < 1; ++i) {
            _spriteBatch.Draw(
                    glm::vec4(0.0f, 0.0f, 50.0f, 50.0f), // Position and dimensions
                    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),  // UV coordinates
                    textureId, // Texture
                    0.0f, // Depth
                    color // Color
            );
        }

        _spriteBatch.End();

        _spriteBatch.Render();

        //for (auto& sprite : _sprites) {
        //    sprite->Draw();
        //}

        glBindTexture(GL_TEXTURE_2D, 0);
        _shader.Unbind();
    }

    // 2. Draw your elements
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    // 3. Swap buffers
    SDL_GL_SwapWindow(_window);
}



