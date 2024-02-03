#include <GL/glew.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

#include "NetworkDaemon.h"
#include "Common/Logging/AppenderConsole.h"

#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

#include <fmt/core.h>
#include <google/protobuf/stubs/common.h>
#include <boost/asio/signal_set.hpp>
#include <string>
#include <sstream>

#include <Common/Asio/IoContext.h>
#include <Common/Logging/Log.h>
#include <Common/Debugging/Errors.h>
#include <csignal>

int quit = false;

void SignalHandler(boost::system::error_code const& error, int /*signalNumber*/)
{
    if (!error) {
        LOG_INFO("engine", "Signal received, shutting down.");
        quit = true;
    }
}

int main(int argc, char** argv) {

    signal(SIGABRT, &Avalon::AbortHandler);

    std::shared_ptr<Avalon::Asio::IoContext> ioContext = std::make_shared<Avalon::Asio::IoContext>();
    sLog->Initialize(ioContext.get());

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    SSL_library_init();
    LOG_DEBUG("system", "OpenSSL library initialized");

    GOOGLE_PROTOBUF_VERIFY_VERSION;
    LOG_DEBUG("system", "Google Protocol Buffers library initialized");

    LOG_INFO("system", "> Using SSL version: {}", OPENSSL_VERSION_TEXT);
    LOG_INFO("system", "> Using Boost version: {}.{}.{}", BOOST_VERSION / 100000, BOOST_VERSION / 100 % 1000, BOOST_VERSION % 100);
    LOG_INFO("system", "> Using Protobuf version: {}.{}.{}", GOOGLE_PROTOBUF_VERSION / 100000, GOOGLE_PROTOBUF_VERSION / 100 % 1000, GOOGLE_PROTOBUF_VERSION % 100);
    LOG_INFO("system", "> Using ImGui version: {}.{}.{} (Docking={})", IMGUI_VERSION_NUM / 10000, IMGUI_VERSION_NUM / 100 % 100, IMGUI_VERSION_NUM % 100, true);

    boost::asio::signal_set signals(*ioContext, SIGINT, SIGTERM);
#if AV_PLATFORM_WIN
    signals.add(SIGBREAK);
#endif

    signals.async_wait(SignalHandler);

    std::shared_ptr<std::vector<std::thread>> threadPool(new std::vector<std::thread>(), [ioContext](std::vector<std::thread>* del)
    {
        ioContext->stop();
        for (std::thread& thr : *del)
            thr.join();

        delete del;
    });

    int numThreads = 2;

    for (int i = 0; i < numThreads; ++i)
    {
        threadPool->emplace_back([ioContext]()
                                          {
                                              ioContext->run();
                                          });
    }

    LOG_INFO("engine", "Starting engine");

    NetworkDaemon daemon;
    daemon.RegisterHandlers();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) < 0) {
        // Handle initialization error
        return -1;
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
    auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Window* window = SDL_CreateWindow(
            "SDL Game Loop",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            window_flags
    ); // SDL_WINDOW_MOUSE_CAPTURE

    if (!window) {
        // Handle window creation error
        return -1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        // Handle context creation error
        return -1;
    }

    SDL_GL_MakeCurrent(window, glContext);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;               // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Initialize GLEW
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        std::cerr << "GLEW initialization failed: " << glewGetErrorString(glewError) << std::endl;
        return 1;
    }

    // Game loop variables
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;

    // Main game loop
    while (!quit) {
        frameStart = SDL_GetTicks();

        // Event handling
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                quit = true;
            if (event.type == SDL_WINDOWEVENT
            && event.window.event == SDL_WINDOWEVENT_CLOSE
            && event.window.windowID == SDL_GetWindowID(window)) {
                quit = true;
            }
        }

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
                daemon.Start();
                SDL_SetWindowSize(window, 1360, 768);
            }

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

            if (ImGui::Button("Quit")) {
                quit = true;
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

        // Game logic update


        // Render your game elements here
        // TODO: Render game elements
        ImGui::Render();

        // Clear the screen
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // Swap buffers
        SDL_GL_SwapWindow(window);

        // Calculate frame time
        auto frameTime = SDL_GetTicks() - frameStart;

        // Cap frame rate
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }

        // Update window title with frame time
        SDL_SetWindowTitle(window, fmt::format("SDL Game Loop - {:.1f} ms/frame ({:.1f} FPS)", 1000.0f / io.Framerate, io.Framerate).c_str());
    }

    threadPool.reset();

    sLog->SetSynchronous();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // Clean up
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    google::protobuf::ShutdownProtobufLibrary();

    LOG_INFO("engine", "Halting process...");

    return 0;
}
