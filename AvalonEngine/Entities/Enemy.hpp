#pragma once

#include <SFML/Graphics.hpp>
#include "Class.hpp"


namespace av
{
	namespace entities 
	{
		class Enemy : public sf::RectangleShape
		{
		public:
			explicit Enemy(sf::Vector2f l_size, Class l_class);
			~Enemy();

			virtual void Update(float timestep);
			virtual void Render(sf::RenderWindow& l_window);

			virtual sf::Vector2f getPosition() { return m_body_.getPosition(); }
			virtual sf::Vector2f getSize() { return m_body_.getSize(); }

		private:
			sf::RectangleShape m_body_;
			Class m_class_;
		};
	}
}



