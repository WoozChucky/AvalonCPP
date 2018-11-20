#pragma once
#include "Audio/AudioPlayer.h"
#include "NullAudioPlayer.h"
#include "FileSystem.h"
#include "Logger.h"
#include "NullFileSystem.h"

namespace av
{

	class Locator
	{
	public:
		static AudioPlayer& GetAudio();
		static FileSystem& GetFileSystem();
		static Logger& GetLogger();

		static void Initialize();

		static void Provide(AudioPlayer* l_service);
		static void Provide(FileSystem* l_service);
		static void Provide(Logger* l_service);

	private:
		static AudioPlayer* m_audio_service_;
		//static NullAudioPlayer m_null_audio_service_;

		static FileSystem* m_fs_service_;
		//static NullFileSystem m_null_fs_service_;

		static Logger* m_logger_service_;
	};
}



