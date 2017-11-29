#pragma once
#include "Audio/AudioPlayer.hpp"
#include "Audio/NullAudioPlayer.hpp"
#include "FileSystem/FileSystem.hpp"
#include "FileSystem/NullFileSystem.hpp"
#include "Logger/Logger.hpp"
#include "Logger/NullLogger.hpp"

namespace av
{
    class Locator
    {
    public:
        static AudioPlayer& GetAudio();
        static FileSystem& GetFileSystem();
        static Logger& GetLogger();

        static void Initialize();

        static void Provide(AudioPlayer* l_service);
        static void Provide(FileSystem* l_service);
        static void Provide(Logger* l_service);

    private:
        static AudioPlayer* m_audio_service_;
        static NullAudioPlayer m_null_audio_service_;

        static FileSystem* m_fs_service_;
        static NullFileSystem m_null_fs_service_;

        static Logger* m_logger_service_;
        static NullLogger m_null_logger_service_;
    };

}