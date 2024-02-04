#include <GL/glew.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

#include "NetworkDaemon.h"
#include "Common/Logging/AppenderConsole.h"
#include "Game.h"
#include "Network/SslContext.h"

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

#include <Common/Asio/IoContext.h>
#include <Common/Logging/Log.h>
#include <Common/Debugging/Errors.h>
#include <csignal>

std::unique_ptr<Game> game;

int quit = false;

void SignalHandler(boost::system::error_code const& error, int /*signalNumber*/)
{
    if (!error) {
        LOG_INFO("engine", "Signal received, shutting down.");
        game->Stop();
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
    if (!SslContext::Initialize("cert-public.pem", ""))
    {
        LOG_ERROR("network.ssl", "Failed to initialize SSL context");
        return 1;
    }

    GOOGLE_PROTOBUF_VERIFY_VERSION;
    LOG_DEBUG("system", "Google Protocol Buffers library initialized");

    IMGUI_CHECKVERSION();
    LOG_DEBUG("system", "ImGui library initialized");

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

    ImGui::CreateContext();
    game = std::make_unique<Game>(*ioContext);
    game->Run();
    game->Shutdown();
    game.reset();

    LOG_INFO("engine", "Engine stopped");

    threadPool.reset();

    sLog->SetSynchronous();

    google::protobuf::ShutdownProtobufLibrary();

    LOG_INFO("system", "Halting process...");

    return 0;
}
