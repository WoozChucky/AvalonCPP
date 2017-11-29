#include "EnemyGraphicsComponent.hpp"
#include "../../Entities/Enemy.hpp"

av::EnemyGraphicsComponent::EnemyGraphicsComponent()
{

}

void av::EnemyGraphicsComponent::Render(av::Entity& l_entity, sf::RenderWindow& l_window)
{
    auto enemy = static_cast<av::Enemy&>(l_entity);

    enemy.GetHealthbar().Render(l_window);
    l_window.draw(enemy.GetBody());
}