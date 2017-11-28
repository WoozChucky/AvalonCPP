#include "Locator.hpp"

av::AudioPlayer* av::Locator::m_audio_service_;
av::NullAudioPlayer av::Locator::m_null_audio_service_;
av::FileSystem* av::Locator::m_fs_service_;
av::NullFileSystem av::Locator::m_null_fs_service_;

void av::Locator::Initialize()
{
    m_audio_service_ = &m_null_audio_service_;
    m_fs_service_ = &m_null_fs_service_;
}

av::AudioPlayer& av::Locator::GetAudio()
{
    return *m_audio_service_;
}

av::FileSystem& av::Locator::GetFileSystem()
{
    return *m_fs_service_;
}

void av::Locator::Provide(AudioPlayer* l_service)
{
    if(l_service == nullptr)
    {
        //Revert to null service.
        m_audio_service_ = &m_null_audio_service_;
    }
    else
    {
        m_audio_service_ = l_service;
    }
}

void av::Locator::Provide(FileSystem* l_service)
{
    if(l_service == nullptr)
    {
        //Revert to null service.
        m_fs_service_ = &m_null_fs_service_;
    }
    else
    {
        m_fs_service_ = l_service;
    }
}