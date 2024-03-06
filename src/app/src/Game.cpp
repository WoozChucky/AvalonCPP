#include "Game.h"
#include <fmt/core.h>
#include <glad/glad.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <Engine/Audio/AudioManager.h>
#include <Engine/Graphics/AssetManager.h>
#include "Common/Logging/Log.h"
#include "Engine/Input/InputManager.h"
#include "Scenes/SceneManager.h"
#include "Scenes/TestingScene.h"
#include "Scenes/MapScene.h"
#include <chrono>

#include <freetype/freetype.h>

void OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    // if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
        LOG_WARN("graphics", "OpenGL Debug Message: {}", message);
    // }
}

void GLFWErrorCallback(int code, const char* description)
{
    LOG_WARN("GLFW", "[{}]: {}", code, description);
}

Game::Game(boost::asio::io_context &ioContext, GameSettings &settings): ioContext(ioContext), _io(ImGui::GetIO()){
    // Initialization code here
    _settings = settings;
    _isRunning = false;
    _networkDaemon = std::make_unique<NetworkDaemon>();
    _networkDaemon->RegisterHandlers();

    if (glfwInit() != GLFW_TRUE) {
        // Handle initialization error
        throw std::runtime_error("glfwInit() failed");
    }

    glfwSetErrorCallback(GLFWErrorCallback);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE); // Should be used for Debug only
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


    _window = glfwCreateWindow(
            (S32) _settings.Video.Resolution.Width,
            (S32) _settings.Video.Resolution.Height,
            "The Title",
            nullptr,
            nullptr
    );

    glfwMakeContextCurrent(_window);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    assert(status);

    const char* glsl_version = "#version 410";

    if (!_window) {
        throw std::runtime_error("SDL_CreateWindow failed");
    }

    _currentResolution = _settings.Video.Resolution.GetResolutionOption();

    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);
    glViewport(0, 0, width, height);

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
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    std::string str(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    LOG_DEBUG("system", "> Using OpenGL version: {}", str.c_str());

    glfwSwapInterval(_settings.Video.VSync ? 1 : 0);
    LOG_INFO("graphics", "VSync: {}", _settings.Video.VSync ? "Enabled" : "Disabled");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);

    sAssetManager->Initialize();

#if 0
    sAudio->Initialize(_settings.Audio, [this](U8 *stream, int len) {
        // Audio recorded callback
        auto audioData = std::vector<U8>(stream, stream + len);
        _networkDaemon->SendAudioPacket(audioData);
    });
#endif

    sSceneManager->Initialize();
    sSceneManager->AddScene("Testing", new TestingScene(), _settings.Video.Resolution.Width, _settings.Video.Resolution.Height);
    //sSceneManager->AddScene("Maping", new MapScene(), _settings.Video.Resolution.Width, _settings.Video.Resolution.Height);
    sSceneManager->SetActiveScene("Testing");
    //sSceneManager->SetActiveScene("Maping");

    LOG_INFO("game", "Game initialized");
}

Game::~Game() {
#if 0
    sAudio->Shutdown();
#endif
    sAssetManager->Shutdown();
    sSceneManager->Shutdown();
}

void Game::Run() {

    _isRunning = true;

    const float SIMULATION_DT = 1.0f / 60.0f;


    // Initialize variables for timing
    auto startTime  = std::chrono::high_resolution_clock::now();
    auto lastFPSUpdateTime = startTime;
    auto lastSimulationUpdateTime = startTime;
    auto lastRenderUpdateTime = startTime;
    double accumulatedSimulationTime = 0.0;
    double accumulatedRenderTime = 0.0;
    int simulationFrames = 0;
    int renderFrames = 0;

    while (_isRunning) {
        // Calculate time since last simulation update
        auto currentTime = std::chrono::high_resolution_clock::now();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1, 1.0f);

        const float RENDER_DT = 1.0f / (F32)_settings.Video.TargetFramesPerSecond;

        if (_transitionToDebug) {
            _debugWindow = !_debugWindow;
            _transitionToDebug = false;
            HandleEvents(SIMULATION_DT);
            Update(SIMULATION_DT);
            Render(RENDER_DT);
            continue;
        }

        if (_debugWindow) {

            // Calculate time since last simulation update
            double simulationDeltaTime = std::chrono::duration<double>(currentTime - lastSimulationUpdateTime).count();
            accumulatedSimulationTime += simulationDeltaTime;
            lastSimulationUpdateTime = currentTime;

            // Update simulation in fixed timestep increments
            while (accumulatedSimulationTime >= SIMULATION_DT) {
                HandleEvents(SIMULATION_DT);
                Update(SIMULATION_DT);
                Render(RENDER_DT);
                accumulatedSimulationTime -= SIMULATION_DT;
                simulationFrames++;
                renderFrames++;
            }

            // Print actual framerates every second
            if (currentTime - lastFPSUpdateTime >= std::chrono::milliseconds(50)) {
                double elapsedTimeSinceFPSUpdate = std::chrono::duration<double>(currentTime - lastFPSUpdateTime).count();

                // Calculate FPS for simulation and rendering
                double simulationFPS = simulationFrames / elapsedTimeSinceFPSUpdate;
                double renderFPS = renderFrames / elapsedTimeSinceFPSUpdate;

                // Update window title with frame time
                // SDL_SetWindowTitle(_window, fmt::format("SDL Game Loop - {:.1f} ms/frame (Rendering FPS: {:.1f} - Simulation FPS: {:.1f})", 1.0f, renderFPS, simulationFPS).c_str());
                simulationFrames = 0;
                renderFrames = 0;
                lastFPSUpdateTime = currentTime;
            }

        } else {

            // Calculate time since last simulation update
            double simulationDeltaTime = std::chrono::duration<double>(currentTime - lastSimulationUpdateTime).count();
            accumulatedSimulationTime += simulationDeltaTime;
            lastSimulationUpdateTime = currentTime;

            // Update simulation in fixed timestep increments
            while (accumulatedSimulationTime >= SIMULATION_DT) {
                HandleEvents(SIMULATION_DT);
                Update(SIMULATION_DT);
                accumulatedSimulationTime -= SIMULATION_DT;
                simulationFrames++;

                LOG_INFO("Update", "1");
            }

            // Calculate time since last render
            double renderDeltaTime = std::chrono::duration<double>(currentTime - lastRenderUpdateTime).count();
            accumulatedRenderTime += renderDeltaTime;
            lastRenderUpdateTime = currentTime;

            // Render in fixed timestep increments
            if (accumulatedRenderTime >= RENDER_DT) {
                Render(RENDER_DT);
                accumulatedRenderTime -= RENDER_DT;
                renderFrames++;

                LOG_INFO("Render", "2");
            }

            // Print actual framerates every second
            if (currentTime - lastFPSUpdateTime >= std::chrono::milliseconds(50)) {
                double elapsedTimeSinceFPSUpdate = std::chrono::duration<double>(currentTime - lastFPSUpdateTime).count();

                // Calculate FPS for simulation and rendering
                double simulationFPS = simulationFrames / elapsedTimeSinceFPSUpdate;
                double renderFPS = renderFrames / elapsedTimeSinceFPSUpdate;

                // Update window title with frame time
                // SDL_SetWindowTitle(_window, fmt::format("SDL Game Loop - {:.1f} ms/frame (Rendering FPS: {:.1f} - Simulation FPS: {:.1f})", 1.0f, renderFPS, simulationFPS).c_str());
                simulationFrames = 0;
                renderFrames = 0;
                lastFPSUpdateTime = currentTime;
            }
        }

        glfwPollEvents();
        glfwSwapBuffers(_window);

        // Sleep to control loop speed
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Clean up
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Game::HandleEvents(F32 deltaTime) {
    sInputManager->Update();
    // Event handling
    /*
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
            case SDL_MOUSEBUTTONDOWN:
                sInputManager->PressKey(event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                sInputManager->ReleaseKey(event.button.button);
                break;
            case SDL_MOUSEMOTION:
                sInputManager->SetMouseCoords(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEWHEEL:
                sInputManager->SetMouseWheel(event.wheel.x, event.wheel.y);
                break;
        }
        sSceneManager->onSDLEvent(event);
    }
    */

    if (sInputManager->IsKeyPressed(1)) {
        _transitionToDebug = !_transitionToDebug;
    }

    if (sInputManager->IsKeyDown(2)) {
        _isRunning = false;
    }
}

void Game::Update(F32 deltaTime) {
    // Start the Dear ImGui frame
    if (_debugWindow) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
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
                //SDL_SetWindowSize(_window, _settings.Video.Resolution.Width, _settings.Video.Resolution.Height);
                //SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
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
#if 0
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
#endif

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
    }

    sSceneManager->Update(deltaTime);
}

void Game::Render(F32 deltaTime) {
    // 1. Clear the screen
    glViewport(0, 0, (int)_settings.Video.Resolution.Width, (int)_settings.Video.Resolution.Height);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sSceneManager->Draw(deltaTime);

    // 2. Draw your elements
    if (_debugWindow) {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    // 3. Swap buffers
    glfwSwapBuffers(_window);
}



