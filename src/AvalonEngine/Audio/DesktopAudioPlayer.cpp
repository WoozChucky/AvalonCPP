//
// Created by Nuno Levezinho on 07/02/2018.
//

#include <iostream>
#include "DesktopAudioPlayer.h"
#include "../Locator.h"


av::DesktopAudioPlayer::DesktopAudioPlayer()
{
    //This has to run on a completely different thread so it doesn't block the UI thread
    this->m_cleanup_thread_ = std::thread(&DesktopAudioPlayer::ClearFinishedSFX, this);
    this->m_cleanup_thread_.detach();
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
    this->m_sfx_thread_ = std::thread(&DesktopAudioPlayer::PlayAsync, this, std::ref(l_sfx), std::ref(l_repeat));
    this->m_sfx_thread_.detach();
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

void av::DesktopAudioPlayer::PlayAsync(const audio::SFX l_sfx, const bool l_repeat)
{
    auto found_buffer = false;

    this->m_mutex_buffer_.lock();

    for(const auto buffer : this->m_sound_buffer_)
    {
        if(buffer.first == l_sfx)
        {
            Locator::GetLogger().Log(__FUNCTION__, "Found existing sound buffer");
            found_buffer = true;
            break;
        }
    }

    if(!found_buffer)
    {
        Locator::GetLogger().Log(__FUNCTION__, "Loading new sound buffer");
        this->m_sound_buffer_[l_sfx].loadFromFile(as_string(l_sfx));
    }

    this->m_sound_.emplace_back(sf::Sound(m_sound_buffer_[l_sfx])); //WARNING: Look at emplace_back vs push_back
    this->m_sound_.at(this->m_sound_.size() - 1).setVolume(m_sfx_volume_);
    this->m_sound_.at(this->m_sound_.size() - 1).setLoop(l_repeat);
    this->m_sound_.at(this->m_sound_.size() - 1).play();

    this->m_mutex_buffer_.unlock();

    std::cout << "Finished AudioPlayer::PlayAsync thread " << std::this_thread::get_id() << std::endl;
}

void av::DesktopAudioPlayer::ClearFinishedSFX()
{
    while (true)
    {
        char buffer[80];
        sprintf(buffer, "buffers cleared -> %d", static_cast<int>(this->m_sound_.size()));
        Locator::GetLogger().Log(__FUNCTION__, buffer);
        this->m_sound_.clear();

        std::this_thread::sleep_for(std::chrono::seconds(30)); //TODO: These 30 seconds need to be tested and should be a #define ?
    }
}
