#pragma once

namespace av::fs
{
	typedef struct Video
	{
		unsigned int Width;
		unsigned int Height;
		unsigned int Bpp;

		Video() = default;

		Video(const unsigned int l_width, const unsigned int l_height, unsigned int l_bpp)
			: Width(l_width), Height(l_height), Bpp(l_bpp)
		{ }

	} Video;

	typedef struct Audio
	{
		unsigned int SFX;
		unsigned int Music;

		Audio() = default;

		Audio(const unsigned int l_sfx, const unsigned int l_music)
			: SFX(l_sfx), Music(l_music)
		{ }

	} Audio;

	typedef struct Configuration
	{
		Video video;
		Audio audio;

		Configuration(const struct Video l_video, const struct Audio l_audio)
			: video(l_video), audio(l_audio) {	}

		Configuration() = default;
	} Configuration;
}