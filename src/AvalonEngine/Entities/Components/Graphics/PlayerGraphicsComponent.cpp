//
// Created by Nuno Levezinho on 07/02/2018.
//

#include "PlayerGraphicsComponent.h"
#include "../../Player.h"

av::PlayerGraphicsComponent::PlayerGraphicsComponent() = default;

void av::PlayerGraphicsComponent::Render(Entity& l_entity, sf::RenderWindow& l_window)
{
    auto player = dynamic_cast<Player&>(l_entity);

    l_window.draw(player);
    l_window.draw(player.GetRifle());
    for (auto i = 0; i < player.GetBullets().size(); i++) {
        l_window.draw(player.GetBullets()[i]);
    }


}