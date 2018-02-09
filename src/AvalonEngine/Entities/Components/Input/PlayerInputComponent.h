//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef PROJECT_PLAYERINPUTCOMPONENT_H
#define PROJECT_PLAYERINPUTCOMPONENT_H

#include "../InputComponent.h"
#include "../../Entity.h"
#include "../../Player.h"

namespace av
{

    class PlayerInputComponent : public InputComponent {
    public:
        PlayerInputComponent();
        void Update(Entity& l_entity, float timestep) override;

    private:
        void Move(Player& player, float timestep);
        void Shoot(Player& player, float timestep);

        //Helper functions
        float GetRotationAngle(Player& player) const;
        sf::Vector2f GetBulletSpawn(Player& player) const;
    };

}


#endif //PROJECT_PLAYERINPUTCOMPONENT_H
