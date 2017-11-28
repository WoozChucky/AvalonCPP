#pragma once

#include <SFML/Audio.hpp>
#include "Audio.hpp"
#include <queue>
#include <map>
#include <list>

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

			std::map<audio::SFX, sf::SoundBuffer> m_sound_buffers_;
			std::list<sf::Sound> m_sound_list_;

            sf::String as_string(audio::MUSIC l_value);
            sf::String as_string(audio::SFX l_value);

            sf::Music m_music_;

			float m_sfx_volume_ = 100;
    };

}
