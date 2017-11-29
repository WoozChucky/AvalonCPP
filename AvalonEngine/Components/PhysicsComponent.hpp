#pragma once
#include "../Entities/Entity.hpp"
#include "../Levels/Level.hpp"

namespace av
{

    class PhysicsComponent
    {
        public:
            virtual ~PhysicsComponent() {};
            virtual void Update(Entity& l_entity /*Level& l_level*/) = 0;
    };

}