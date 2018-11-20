#pragma once

#include "Audio/AudioPlayer.h"

namespace av
{
	class NullAudioPlayer : public AudioPlayer
	{
	public:
		NullAudioPlayer() = default;

		void PlaySFX(audio::SFX, bool) override {}
		void PlayMusic(audio::MUSIC, bool) override {}

		void SetSFXVolume(float) override {}
		void SetMusicVolume(float) override {}

		void PauseSFX() override {}
		void PauseMusic() override {}

		void StopSFX() override {}
		void StopMusic() override {}
	};
}