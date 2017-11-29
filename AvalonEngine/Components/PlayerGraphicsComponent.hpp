#pragma once

#include "GraphicsComponent.hpp"

namespace av
{

    class PlayerGraphicsComponent : public GrapicsComponent
    {
        public:
            PlayerGraphicsComponent();
            void Render(av::Entity& l_entity, sf::RenderWindow& l_window) override;
    };

}