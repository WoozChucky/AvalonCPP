#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <chrono>
#include <math.h>
#include <iostream>
#include "Bullet.hpp"

namespace av
{
	namespace entities 
	{
		class Player : public sf::CircleShape
		{
		public:
			Player();
			
			void Update(float timestep);
			void Render(sf::RenderWindow& l_window);
			void HandleInput(sf::Event l_event);
			float x() const;
			float y() const;
			float Left() const;
			float Right() const;
			float Top() const;
			float Bottom() const;
			void Move(float timestep);
			void Shoot(float timestep);
			float getRotationAngle() const;
			void Restart();
			sf::Vector2f getBulletSpawn() const;

			std::vector<Bullet> m_bullets;

		private:
			sf::Vector2f m_mouse_position_;
			sf::Vector2f m_velocity_;
			float m_player_velocity_;
			// timer for the bullet spawn 
			std::chrono::time_point<std::chrono::system_clock> m_spawn_time_;
			// side size to render it properly
			float m_side_distance_;

			// 
			sf::RectangleShape m_rifle_;
		};
	}

}



