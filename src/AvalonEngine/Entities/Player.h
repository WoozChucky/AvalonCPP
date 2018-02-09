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

        std::vector<Bullet> GetBullets() const;
        sf::RectangleShape GetRifle() const;
        sf::FloatRect GetGlobalBounds() override;



        //All of these should be refractored with getters and setters

        float Left() const;
        float Right() const;

        sf::Vector2f m_mouse_position_;



        // Getters/Setters
        sf::RectangleShape& getRifle();
        void setRifle(sf::RectangleShape l_rifle);

        sf::Vector2f& getVelocity();
        void setVelocity(sf::Vector2f l_velocity);

        float getPlayerVelocity() const;
        void setPlayerVelocity(float l_velocity);

        std::chrono::time_point<std::chrono::system_clock> getSpawnTime() const;
        void setSpawnTime(std::chrono::time_point<std::chrono::system_clock> l_time);

        std::vector<Bullet>& getBullets();
    private:

        // side size to render it properly
        float m_side_distance_;
        float m_player_velocity_;
        sf::Vector2f m_velocity_;

        //Weapons & Tools
        sf::RectangleShape m_rifle_;
        std::vector<Bullet> m_bullets_;

        // timer for the bullet spawn
        std::chrono::time_point<std::chrono::system_clock> m_spawn_time_;

        float X() const;
        float Y() const;
        float Top() const;
        float Bottom() const;

        //Components
        GrapicsComponent* 	m_graphics_;
        InputComponent* 	m_input_;
        //PhysicsComponent*	m_physics_;
    };

}


#endif //AVALONENGINE_PLAYER_H
