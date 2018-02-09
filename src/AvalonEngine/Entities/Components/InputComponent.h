//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_INPUTCOMPONENT_H
#define AVALONENGINE_INPUTCOMPONENT_H

#include "../Entity.h"

namespace av
{

    class InputComponent
    {
    public:
        ~InputComponent() = default;
        virtual void Update(Entity& l_entity, float timestep) = 0;
    };

}

#endif //AVALONENGINE_INPUTCOMPONENT_H
