#pragma once
#include "Audio/AudioPlayer.hpp"
#include "Audio/NullAudioPlayer.hpp"

namespace av
{
    //TODO: Tear down this class in cpp impl as well.
    class Locator
    {
    public:
        static AudioPlayer& GetAudio();

        static void Initialize();

        static void Provide(AudioPlayer* l_service);

    private:
        static AudioPlayer* m_audio_service_;
        static NullAudioPlayer m_null_audio_service_;
    };

}