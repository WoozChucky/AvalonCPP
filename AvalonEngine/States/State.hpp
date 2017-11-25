#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

namespace av
{
	namespace state
	{
		class State
		{
		public:
			State(sf::Vector2f l_window_size);

			void virtual Update(float timestep) = 0;
			void virtual Render(sf::RenderWindow& l_window) = 0;
			void virtual HandleInput(sf::Event l_event) = 0;

			sf::Vector2f m_window_size;			
		};
	}
}
