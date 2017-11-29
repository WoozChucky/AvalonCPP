#include "PlayerGraphicsComponent.hpp"
#include "../../Entities/Player.hpp"

av::PlayerGraphicsComponent::PlayerGraphicsComponent()
{

}

void av::PlayerGraphicsComponent::Render(Entity& l_entity, sf::RenderWindow& l_window)
{
    auto player = static_cast<Player&>(l_entity);

    l_window.draw(player);
	l_window.draw(player.GetRifle());
	for (auto i = 0; i < player.GetBullets().size(); i++) {
		l_window.draw(player.GetBullets()[i]);
	}

    
}