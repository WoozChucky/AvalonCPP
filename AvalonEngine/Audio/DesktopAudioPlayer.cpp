#include "DesktopAudioPlayer.hpp"
#include <thread>

av::DesktopAudioPlayer::DesktopAudioPlayer() 
{
	m_sound_buffers_[audio::SFX::RIFLE_SHOOT_NORMAL].loadFromFile(as_string(audio::SFX::RIFLE_SHOOT_NORMAL));
	m_sound_buffers_[audio::SFX::BASIC_ENEMY_DIE].loadFromFile(as_string(audio::SFX::BASIC_ENEMY_DIE));
}

av::DesktopAudioPlayer::~DesktopAudioPlayer() {}

void av::DesktopAudioPlayer::PlayMusic(const audio::MUSIC l_music, const bool l_repeat)
{
	const auto file_path = as_string(l_music);

    this->m_music_.openFromFile(file_path);
    this->m_music_.setLoop(l_repeat);
    this->m_music_.setVolume(m_music_volume_);
    this->m_music_.play();
}

void av::DesktopAudioPlayer::PlaySFX(const audio::SFX l_sfx, const bool l_repeat)
{
    sf::Sound sfx(m_sound_buffers_[l_sfx]);
    sfx.setLoop(l_repeat);
    sfx.setVolume(this->m_sfx_volume_);
    sfx.play();

    

    std::thread sfx_thread(&av::DesktopAudioPlayer::PlayAsync, this, std::ref(sfx));
    sfx_thread.join();

    std::cout << "Sound buffer duration -> " << sfx.getBuffer()->getDuration().asSeconds() << std::endl;
}

void av::DesktopAudioPlayer::SetSFXVolume(const float l_volume)
{
    this->m_sfx_volume_ = l_volume;
}

void av::DesktopAudioPlayer::SetMusicVolume(const float l_volume)
{
    this->m_music_.setVolume(l_volume);
}

void av::DesktopAudioPlayer::PauseSFX()
{
    //this->m_sound_.pause();
}

void av::DesktopAudioPlayer::PauseMusic()
{
    this->m_music_.pause();
}

void av::DesktopAudioPlayer::StopSFX()
{
    //this->m_sound_.stop();
}

void av::DesktopAudioPlayer::StopMusic()
{
    this->m_music_.stop();
}

sf::String av::DesktopAudioPlayer::as_string(const audio::SFX l_value)
{
    switch(l_value)
    {
        case audio::SFX::RIFLE_SHOOT_NORMAL:
            return "Assets/SFX/shoot_normal.wav";
        case audio::SFX::BASIC_ENEMY_DIE:
            return "Assets/SFX/fart.wav";
    }
    throw "Invalid SFX";
}

sf::String av::DesktopAudioPlayer::as_string(const audio::MUSIC l_value)
{
    switch(l_value)
    {
        case audio::MUSIC::INTRO:
            return "Assets/SFX/shoot_normal.wav";
        case audio::MUSIC::LEVEL1:
            return "Assets/SFX/fart.wav";
        case audio::MUSIC::LEVEL2:
        case audio::MUSIC::BOSS:
            throw "Invalid MUSIC";
    }
    throw "Invalid MUSIC";
}

void av::DesktopAudioPlayer::PlayAsync(sf::Sound& l_sound)
{
    std::cout << "Started new play thread" << std::endl;
    l_sound.play();
}