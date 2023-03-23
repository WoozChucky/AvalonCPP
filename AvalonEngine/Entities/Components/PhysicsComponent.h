//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_PHYSICSCOMPONENT_H
#define AVALONENGINE_PHYSICSCOMPONENT_H

#include "../Entity.h"

namespace av
{

    class PhysicsComponent
    {
    public:
        virtual ~PhysicsComponent() {};
        virtual void Update(Entity& l_entity) = 0;
    };

}

#endif //AVALONENGINE_PHYSICSCOMPONENT_H
