//
// Created by Nuno Levezinho on 07/02/2018.
//

#include <iostream>
#include "NullAudioPlayer.h"

void av::NullAudioPlayer::PlaySFX(audio::SFX, bool)
{
    std::cout << "NullAudioPlayer.PlaySFX()" << std::endl;
}

void av::NullAudioPlayer::PlayMusic(audio::MUSIC, bool)
{
    std::cout << "NullAudioPlayer.PlayMusic()" << std::endl;
}

void av::NullAudioPlayer::SetSFXVolume(float)
{

}

void av::NullAudioPlayer::SetMusicVolume(float)
{

}

void av::NullAudioPlayer::PauseSFX()
{

}

void av::NullAudioPlayer::PauseMusic()
{

}

void av::NullAudioPlayer::StopSFX()
{

}

void av::NullAudioPlayer::StopMusic()
{

}