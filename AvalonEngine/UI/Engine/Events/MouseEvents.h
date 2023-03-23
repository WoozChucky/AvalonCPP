//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_MOUSEEVENTS_H
#define AVALONENGINE_MOUSEEVENTS_H

namespace av
{
    class MouseClickCallback
    {
    public:
        virtual ~MouseClickCallback() = default;
        virtual void Execute() = 0;
    };

    class MouseOverEnterCallback
    {
    public:
        virtual ~MouseOverEnterCallback() = default;
        virtual void Execute() = 0;
    };

    class MouseOverExitCallback
    {
    public:
        virtual ~MouseOverExitCallback() = default;
        virtual void Execute() = 0;
    };
}

#endif //AVALONENGINE_MOUSEEVENTS_H
