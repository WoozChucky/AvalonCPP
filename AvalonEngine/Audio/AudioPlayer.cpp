#include "AudioPlayer.hpp"

av::AudioPlayer::AudioPlayer() 
{
	m_sound_buffers_[audio::SFX::RIFLE_SHOOT_NORMAL].loadFromFile(as_string(audio::SFX::RIFLE_SHOOT_NORMAL));
	m_sound_buffers_[audio::SFX::BASIC_ENEMY_DIE].loadFromFile(as_string(audio::SFX::BASIC_ENEMY_DIE));
}

av::AudioPlayer& av::AudioPlayer::Instance()
{
    static AudioPlayer *instance = new AudioPlayer();
    return *instance;
}

void av::AudioPlayer::PlayMusic(const audio::MUSIC l_music, const bool l_repeat)
{
	const auto file_path = as_string(l_music);

    this->m_music_.openFromFile(file_path);
    this->m_music_.setLoop(l_repeat);
    this->m_music_.setVolume(m_sfx_volume_);
    this->m_music_.play();
}

void av::AudioPlayer::PlaySFX(const audio::SFX l_sfx, const bool l_repeat)
{
	this->m_sound_list_.push_back(sf::Sound(m_sound_buffers_[l_sfx]));
	this->m_sound_list_.end()->setLoop(l_repeat);
	this->m_sound_list_.end()->play();
}

void av::AudioPlayer::SetSFXVolume(const float l_volume)
{
    this->m_sfx_volume_ = l_volume;
}

void av::AudioPlayer::SetMusicVolume(const float l_volume)
{
    this->m_music_.setVolume(l_volume);
}

void av::AudioPlayer::PauseSFX()
{
    //this->m_sound_.pause();
}

void av::AudioPlayer::PauseMusic()
{
    this->m_music_.pause();
}

void av::AudioPlayer::StopSFX()
{
    //this->m_sound_.stop();
}

void av::AudioPlayer::StopMusic()
{
    this->m_music_.stop();
}

sf::String av::AudioPlayer::as_string(const audio::SFX l_value)
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

sf::String av::AudioPlayer::as_string(const audio::MUSIC l_value)
{
    switch(l_value)
    {
        case audio::MUSIC::INTRO:
            return "Assets/SFX/shoot_normal.wav";
        case audio::MUSIC::LEVEL1:
            return "Assets/SFX/fart.wav";
    }
    throw "Invalid MUSIC";
}