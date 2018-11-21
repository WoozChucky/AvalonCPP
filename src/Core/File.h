#pragma once

namespace av::fs
{
	typedef struct Video
	{
		unsigned int Width;
		unsigned int Height;
		unsigned int Bpp;
	} Video;

	typedef struct Audio
	{
		unsigned int SFX;
		unsigned int Music;
	} Audio;

	typedef struct Configuration
	{
		Video video_l;
		Audio audio_l;
	} Configuration;
}