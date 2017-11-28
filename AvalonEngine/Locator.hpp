#pragma once
#include "Audio/AudioPlayer.hpp"
#include "Audio/NullAudioPlayer.hpp"
#include "FileSystem/FileSystem.hpp"
#include "FileSystem/NullFileSystem.hpp"

namespace av
{
    //TODO: Tear down this class in cpp impl as well.
    class Locator
    {
    public:
        static AudioPlayer& GetAudio();
        static FileSystem& GetFileSystem();

        static void Initialize();

        static void Provide(AudioPlayer* l_service);
        static void Provide(FileSystem* l_service);

    private:
        static AudioPlayer* m_audio_service_;
        static NullAudioPlayer m_null_audio_service_;

        static FileSystem* m_fs_service_;
        static NullFileSystem m_null_fs_service_;
    };

}