#pragma once

#include "../GraphicsComponent.hpp"

namespace av
{

    class EnemyGraphicsComponent : public GrapicsComponent
    {
        public:
            EnemyGraphicsComponent();
            void Render(av::Entity& l_entity, sf::RenderWindow& l_window) override;
    };

}