//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_LOCATOR_H
#define AVALONENGINE_LOCATOR_H

#include "Audio/AudioPlayer.h"
#include "Audio/NullAudioPlayer.h"
#include "FileSystem/FileSystem.h"
#include "FileSystem/NullFileSystem.h"
#include "Logger/Logger.h"

namespace av
{
    class Locator
    {
    public:
        static AudioPlayer& GetAudio();
        static FileSystem& GetFileSystem();
        static Logger& GetLogger();
        static Logger& GetLogger(typelog l_type);

        static void Initialize();

        static void Provide(AudioPlayer* l_service);
        static void Provide(FileSystem* l_service);
        static void Provide(Logger* l_service);

    private:
        static AudioPlayer* m_audio_service_;
        static NullAudioPlayer m_null_audio_service_;

        static FileSystem* m_fs_service_;
        static NullFileSystem m_null_fs_service_;

        static Logger* m_logger_service_;
    };

}


#endif //AVALONENGINE_LOCATOR_H
