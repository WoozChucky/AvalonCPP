//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_ENTITY_H
#define AVALONENGINE_ENTITY_H

#include <SFML/Graphics.hpp>

namespace av {

    class Entity
    {
    public:
        Entity() = default;;
        virtual ~Entity() = default;;

        virtual void Update(float timestep) = 0;
        virtual void Render(sf::RenderWindow& l_window) = 0;
        virtual void HandleInput(sf::Event l_event) = 0;

        virtual bool IsAlive() = 0;
        virtual bool Collide(Entity& l_entity) = 0;

        virtual sf::FloatRect GetGlobalBounds() = 0;

    };

}

#endif //AVALONENGINE_ENTITY_H
