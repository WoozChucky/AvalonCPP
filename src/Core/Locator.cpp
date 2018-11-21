#include "Locator.h"


using namespace av;

AudioPlayer* Locator::m_AudioService;
FileSystem* Locator::m_FileSystemService;
Logger* Locator::m_LoggerService;

AudioPlayer& Locator::GetAudio()
{
	return *m_AudioService;
}

FileSystem& Locator::GetFileSystem()
{
	return *m_FileSystemService;
}

Logger& Locator::GetLogger(const typelog type)
{
	/** TODO: Fix this
	 * At the moment we have a leak!
	 * This happens because of the output template using the operator << to display more info.
	if (m_LoggerService == nullptr)
		m_LoggerService = new Logger(type);

	if (m_LoggerService->GetLevel() != type)
		m_LoggerService->SetLevel(type);

	return *m_LoggerService;
	*/

	return *new Logger(type);
}

void Locator::Provide(AudioPlayer* l_service)
{
	if (l_service != nullptr)
	{
		m_AudioService = l_service;
	}
}

void Locator::Provide(FileSystem* l_service)
{
	if (l_service != nullptr)
	{
		//Revert to null service.
		m_FileSystemService = l_service;
	}
}

void Locator::Provide(Logger* l_service)
{
	if (l_service == nullptr)
	{
		//Revert to null service.
		throw "Null Logger service";
	}
	
	m_LoggerService = l_service;
}
