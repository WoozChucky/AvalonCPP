//
// Created by Nuno Levezinho on 07/02/2018.
//

#include <iostream>
#include "NullAudioPlayer.h"

av::NullAudioPlayer::NullAudioPlayer()
{

}

void av::NullAudioPlayer::PlaySFX(audio::SFX l_sfx, bool l_repeat)
{
    std::cout << "NullAudioPlayer.PlaySFX()" << std::endl;
}

void av::NullAudioPlayer::PlayMusic(audio::MUSIC l_music, bool l_repeat)
{
    std::cout << "NullAudioPlayer.PlayMusic()" << std::endl;
}

void av::NullAudioPlayer::SetSFXVolume(float l_volume)
{

}

void av::NullAudioPlayer::SetMusicVolume(float l_volume)
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