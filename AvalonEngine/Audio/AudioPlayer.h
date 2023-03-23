//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_AUDIOPLAYER_H
#define AVALONENGINE_AUDIOPLAYER_H

#include "Audio.h"

namespace av {

    class AudioPlayer {
    public:
        virtual ~AudioPlayer() = default;

        virtual void PlaySFX(audio::SFX l_sfx, bool l_repeat) = 0;
        virtual void PlayMusic(audio::MUSIC l_music, bool l_repeat) = 0;

        virtual void SetSFXVolume(float l_volume) = 0;
        virtual void SetMusicVolume(float l_volume) = 0;

        virtual void PauseSFX() = 0;
        virtual void PauseMusic() = 0;

        virtual void StopSFX() = 0;
        virtual void StopMusic() = 0;
    };

}

#endif //AVALONENGINE_AUDIOPLAYER_H
