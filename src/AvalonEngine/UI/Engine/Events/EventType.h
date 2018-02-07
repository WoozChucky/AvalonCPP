//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_EVENTTYPE_H
#define AVALONENGINE_EVENTTYPE_H

namespace av
{

    namespace EventType
    {
        enum class State
        {
            MENU        = 1000,
            GAME        = 1001,
            PAUSE       = 1002,
            HIGHSCORE   = 1003,
            OPTIONS     = 1004,
            PREVIOUS    = 1998,
            EXIT        = 1999
        };

        enum class Level
        {
            RESTART     = 2000,
            PAUSE       = 2001,
            RESUME      = 2002,
            NEXT        = 2003,
            PREVIOUS    = 2004
        };
    };

}

#endif //AVALONENGINE_EVENTTYPE_H
