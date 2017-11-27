#pragma once
#include <SFML/Graphics.hpp>
#include "../Entities/Entity.hpp"

namespace av
{

    class GrapicsComponent
    {
        public:
            virtual ~GrapicsComponent() {};
            virtual void Render(Entity& l_entity, sf::RenderWindow& l_window) = 0;
    };

}