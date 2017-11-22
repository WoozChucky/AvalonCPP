#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

namespace av
{
	namespace state
	{
		class State
		{
		public:
			void virtual Update(float timestep) = 0;
			void virtual Render(sf::RenderWindow& l_window) = 0;
			void virtual HandleInput() = 0;
		};
	}
}
