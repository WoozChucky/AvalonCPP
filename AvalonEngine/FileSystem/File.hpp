#pragma once

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
            Video Video;
            Audio Audio;
        } Configuration;

    }

}