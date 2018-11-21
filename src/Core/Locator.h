#pragma once
#include "Audio/AudioPlayer.h"
#include "FileSystem.h"
#include "Logger.h"

namespace av
{

	class Locator
	{
	public:
		static AudioPlayer& GetAudio();
		static FileSystem& GetFileSystem();
		static Logger& GetLogger(typelog type = DEBUG);

		static void Provide(AudioPlayer* l_service);
		static void Provide(FileSystem* l_service);
		static void Provide(Logger* l_service);

	private:
		static AudioPlayer* m_AudioService;

		static FileSystem* m_FileSystemService;

		static Logger* m_LoggerService;
	};
}



