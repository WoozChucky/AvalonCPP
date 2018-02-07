//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_PLAYER_H
#define AVALONENGINE_PLAYER_H

#include <chrono>
#include "Components/InputComponent.h"
#include "Components/GraphicsComponent.h"
#include "Bullet.h"

namespace av
{
    class Player : public Entity, public sf::CircleShape
    {
    public:
        explicit Player();

        void Update(float timestep) override;
        void Render(sf::RenderWindow& l_window) override;
        void HandleInput(sf::Event l_event) override;
        bool IsAlive() override;
        bool Collide(Entity& l_entity) override;


        void Restart();
        sf::Vector2f GetBulletSpawn() const;

        std::vector<Bullet> GetBullets() const;
        sf::RectangleShape GetRifle() const;
        sf::FloatRect GetGlobalBounds() override;

        std::vector<Bullet> m_bullets_;



    private:
        sf::Vector2f m_mouse_position_;
        sf::Vector2f m_velocity_;
        float m_player_velocity_;
        sf::RectangleShape m_rifle_;
        // timer for the bullet spawn
        std::chrono::time_point<std::chrono::system_clock> m_spawn_time_;
        // side size to render it properly
        float m_side_distance_;


        float X() const;
        float Y() const;
        float Left() const;
        float Right() const;
        float Top() const;
        float Bottom() const;
        void Move(float timestep);
        void Shoot(float timestep);
        float GetRotationAngle() const;

        //Components
        GrapicsComponent* 	m_graphics_;
        InputComponent* 	m_input_;
        //PhysicsComponent*	m_physics_;
    };

}


#endif //AVALONENGINE_PLAYER_H
