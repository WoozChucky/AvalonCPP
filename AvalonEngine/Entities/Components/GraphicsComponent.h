//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_GRAPHICSCOMPONENT_H
#define AVALONENGINE_GRAPHICSCOMPONENT_H

#include <SFML/Graphics.hpp>
#include "../Entity.h"

namespace av
{

    class GrapicsComponent
    {
    public:
        virtual ~GrapicsComponent() = default;;
        virtual void Render(Entity& l_entity, sf::RenderWindow& l_window) = 0;
    };

}

#endif //AVALONENGINE_GRAPHICSCOMPONENT_H
