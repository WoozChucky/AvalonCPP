#pragma once

#include "AudioPlayer.hpp"
#include "Audio.hpp"

namespace av
{
    class NullAudioPlayer : public AudioPlayer
    {
        public:
            NullAudioPlayer();

            void PlaySFX(audio::SFX l_sfx, bool l_repeat = false) override;
            void PlayMusic(audio::MUSIC l_music, bool l_repeat = false) override;

            void SetSFXVolume(float l_volume) override;
            void SetMusicVolume(float l_volume) override;

            void PauseSFX() override;
            void PauseMusic() override;

            void StopSFX() override;
            void StopMusic() override;

        private:
    };
}