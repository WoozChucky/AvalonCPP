#include "DesktopAudioPlayer.hpp"
#include <thread>

av::DesktopAudioPlayer::DesktopAudioPlayer() 
{

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
    std::thread sfx_thread(&av::DesktopAudioPlayer::PlayAsync, this, std::ref(l_sfx), std::ref(l_repeat));
    sfx_thread.join();
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

void av::DesktopAudioPlayer::PlayAsync(audio::SFX l_sfx, bool l_repeat)
{
    std::cout << "Started new play thread" << std::endl;

    bool found_buffer = false;

    m_mutex_buffer_.lock();

    for(auto buffer : m_sound_buffer_)
    {
        if(buffer.first == l_sfx)
        {
            std::cout << "Found existing sound buffer" << std::endl;
            found_buffer = true;
        }
    }

    if(!found_buffer)
    {
        std::cout << "Loading new buffer..." << std::endl;
        m_sound_buffer_[l_sfx].loadFromFile(as_string(l_sfx));
    }

    m_sound_.push_back(sf::Sound(m_sound_buffer_[l_sfx]));
    m_sound_.at(m_sound_.size() - 1).setVolume(m_sfx_volume_);
    m_sound_.at(m_sound_.size() - 1).setLoop(l_repeat);
    m_sound_.at(m_sound_.size() - 1).play();

    m_mutex_buffer_.unlock();

    //std::cout << "Sound buffer duration -> " << m_sound_[index].getBuffer()->getDuration().asSeconds() << std::endl;
}