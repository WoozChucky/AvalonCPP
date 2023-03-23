//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_ENEMYGRAPHICSCOMPONENT_H
#define AVALONENGINE_ENEMYGRAPHICSCOMPONENT_H


#include "../GraphicsComponent.h"

namespace av
{

    class EnemyGraphicsComponent : public GrapicsComponent
    {
    public:
        EnemyGraphicsComponent();
        void Render(av::Entity& l_entity, sf::RenderWindow& l_window) override;
    };

}


#endif //AVALONENGINE_ENEMYGRAPHICSCOMPONENT_H
