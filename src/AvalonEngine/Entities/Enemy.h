//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_ENEMY_H
#define AVALONENGINE_ENEMY_H


#include <SFML/Graphics.hpp>
#include "../UI/Game/Healthbar.h"
#include "Components/GraphicsComponent.h"
#include "Player.h"


namespace av
{
    class Enemy : public Entity, public sf::RectangleShape
    {
    public:
        explicit Enemy(sf::Vector2f l_size);

        void Update(float timestep) override;
        void Render(sf::RenderWindow& l_window) override;
        void HandleInput(sf::Event l_event) override;
        bool Collide(Entity& l_entity) override;

        void setPosition(sf::Vector2f l_position);
        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;
        RectangleShape getBody();

        bool IsAlive() override;
        bool Collide(Bullet& l_entity);
        bool Collide(Enemy l_entity);
        bool Collide(Player& l_entity) const;

        Healthbar GetHealthbar();
        RectangleShape GetBody();

        sf::FloatRect GetGlobalBounds() override;

    private:
        void TakeDamage(sf::Uint32 l_damage);

        RectangleShape m_body_;
        Healthbar m_healthbar_;

        bool m_alive_;

        //Components
        av::GrapicsComponent* m_graphics_;
        //av::PhysicsComponent* m_physics_;
    };
}


#endif //AVALONENGINE_ENEMY_H
