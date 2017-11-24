#pragma once

#include <SFML/Graphics.hpp>
#include "Class.hpp"
#include "../GameUI/Healthbar.hpp"
#include "Bullet.hpp"
#include "Player.hpp"


namespace av
{
	namespace entities 
	{
		class Enemy : public sf::RectangleShape
		{
		public:
			explicit Enemy(sf::Vector2f l_size, Class l_class);

			virtual void Update(float timestep);
			virtual void Render(sf::RenderWindow& l_window);

			sf::Vector2f getPosition();
			sf::Vector2f getSize();

			void TakeDamage(sf::Uint32 l_damage);
			bool IsAlive();
			bool Collide(Bullet& l_entity);
			bool Collide(Player& l_entity);

		private:
			sf::RectangleShape m_body_;

			ui::Healthbar m_healthbar_;

			Class m_class_;

			bool m_alive_;
		};
	}
}



