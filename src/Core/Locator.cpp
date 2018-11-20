#include "Locator.h"


using namespace av;

AudioPlayer* Locator::m_audio_service_;
// NullAudioPlayer Locator::m_null_audio_service_;
FileSystem* Locator::m_fs_service_;
// NullFileSystem Locator::m_null_fs_service_;
Logger* Locator::m_logger_service_;

void Locator::Initialize()
{
	// m_audio_service_ = &m_null_audio_service_;
	// m_fs_service_ = &m_null_fs_service_;
}

AudioPlayer& Locator::GetAudio()
{
	return *m_audio_service_;
}

FileSystem& Locator::GetFileSystem()
{
	return *m_fs_service_;
}

Logger& Locator::GetLogger(const typelog type)
{
	if (m_logger_service_ == nullptr)
		m_logger_service_ = new Logger(type);

	return *m_logger_service_;
}

void Locator::Provide(AudioPlayer* l_service)
{
	if (l_service == nullptr)
	{
		//Revert to null service.
		// m_audio_service_ = &m_null_audio_service_;
	}
	else
	{
		m_audio_service_ = l_service;
	}
}

void Locator::Provide(FileSystem* l_service)
{
	if (l_service == nullptr)
	{
		//Revert to null service.
		// m_fs_service_ = &m_null_fs_service_;
	}
	else
	{
		m_fs_service_ = l_service;
	}
}

void Locator::Provide(Logger* l_service)
{
	if (l_service == nullptr)
	{
		//Revert to null service.
		throw "Null Logger service";
	}
	
	m_logger_service_ = l_service;
}
