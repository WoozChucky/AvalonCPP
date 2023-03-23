//
// Created by Nuno Levezinho on 07/02/2018.
//

#include "EnemyGraphicsComponent.h"
#include "../../Enemy.h"

av::EnemyGraphicsComponent::EnemyGraphicsComponent() = default;

void av::EnemyGraphicsComponent::Render(av::Entity& l_entity, sf::RenderWindow& l_window)
{
    auto enemy = dynamic_cast<av::Enemy&>(l_entity);

    enemy.GetHealthbar().Render(l_window);
    l_window.draw(enemy.GetBody());
}