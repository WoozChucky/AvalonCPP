#pragma once

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
    };

}