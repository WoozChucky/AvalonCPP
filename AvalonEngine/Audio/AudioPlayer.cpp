#include "AudioPlayer.hpp"

av::AudioPlayer::AudioPlayer() 
{

}

av::AudioPlayer& av::AudioPlayer::Instance()
{
    static AudioPlayer *instance = new AudioPlayer();
    return *instance;
}

void av::AudioPlayer::PlayMusic(audio::MUSIC l_music, bool l_repeat)
{
    auto file_path = as_string(l_music);

    this->m_music_.openFromFile(file_path);
    this->m_music_.setLoop(l_repeat);
    this->m_music_.play();
}

void av::AudioPlayer::PlaySFX(audio::SFX l_sfx, bool l_repeat)
{
    auto file_path = as_string(l_sfx);

    this->m_sound_buffer_.loadFromFile(file_path);
    this->m_sound_.setBuffer(m_sound_buffer_);
    this->m_sound_.setLoop(l_repeat);
    this->m_sound_.play();
}

void av::AudioPlayer::SetSFXVolume(float l_volume)
{
    this->m_sound_.setVolume(l_volume);
}

void av::AudioPlayer::SetMusicVolume(float l_volume)
{
    this->m_music_.setVolume(l_volume);
}

void av::AudioPlayer::PauseSFX()
{
    this->m_sound_.pause();
}

void av::AudioPlayer::PauseMusic()
{
    this->m_music_.pause();
}

void av::AudioPlayer::StopSFX()
{
    this->m_sound_.stop();
}

void av::AudioPlayer::StopMusic()
{
    this->m_music_.stop();
}

sf::String av::AudioPlayer::as_string(audio::SFX l_value)
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

sf::String av::AudioPlayer::as_string(audio::MUSIC l_value)
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