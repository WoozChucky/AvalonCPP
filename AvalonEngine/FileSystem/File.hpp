#pragma once

namespace av
{

    namespace fs
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
            Video Video;
            Audio Audio;
        } Configuration;

    }

}