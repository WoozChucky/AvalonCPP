//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_PLAYERGRAPHICSCOMPONENT_H
#define AVALONENGINE_PLAYERGRAPHICSCOMPONENT_H


#include "../GraphicsComponent.h"

namespace av
{

    class PlayerGraphicsComponent : public GrapicsComponent
    {
    public:
        PlayerGraphicsComponent();
        void Render(av::Entity& l_entity, sf::RenderWindow& l_window) override;
    };

}


#endif //AVALONENGINE_PLAYERGRAPHICSCOMPONENT_H
