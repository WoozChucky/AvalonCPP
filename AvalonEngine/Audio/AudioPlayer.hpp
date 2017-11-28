#pragma once

#include "Audio.hpp"
#include <iostream>

namespace av
{

    class AudioPlayer
    {
        public:
            virtual ~AudioPlayer() {}

            virtual void PlaySFX(audio::SFX l_sfx, bool l_repeat = false) = 0;
            virtual void PlayMusic(audio::MUSIC l_music, bool l_repeat = false) = 0;

            virtual void SetSFXVolume(float l_volume) = 0;
            virtual void SetMusicVolume(float l_volume) = 0;

            virtual void PauseSFX() = 0;
            virtual void PauseMusic() = 0;

            virtual void StopSFX() = 0;
            virtual void StopMusic() = 0;
    };

}
