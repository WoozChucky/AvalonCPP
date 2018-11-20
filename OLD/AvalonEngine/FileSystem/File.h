//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_FILE_H
#define AVALONENGINE_FILE_H

namespace av
{

    namespace fs
    {

        typedef struct VideoS
        {
            unsigned int Width;
            unsigned int Height;
            unsigned int Bpp;
        } Video;

        typedef struct AudioS
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

}

#endif //AVALONENGINE_FILE_H
