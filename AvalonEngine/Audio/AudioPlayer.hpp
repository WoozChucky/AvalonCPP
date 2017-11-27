#pragma once

#include <SFML/Audio.hpp>
#include "Audio.hpp"

namespace av
{

    class AudioPlayer
    {
        public:
            static AudioPlayer& Instance();

            void PlaySFX(audio::SFX l_sfx, bool l_repeat = false);
            void PlayMusic(audio::MUSIC l_music, bool l_repeat = false);

            void SetSFXVolume(float l_volume);
            void SetMusicVolume(float l_volume);

            void PauseSFX();
            void PauseMusic();

            void StopSFX();
            void StopMusic();

        private:
            // hide constructor
            AudioPlayer();

            sf::String as_string(audio::MUSIC l_value);
            sf::String as_string(audio::SFX l_value);

            sf::SoundBuffer m_sound_buffer_;
		    sf::Sound m_sound_;
            sf::Music m_music_;
    };

}