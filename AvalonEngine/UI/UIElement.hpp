#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace av
{
	namespace ui
	{
		class UIElement
		{
		protected:
			~UIElement() = default;

		public:

			virtual void Update(float timestep) = 0;

			virtual void Render(sf::RenderWindow& l_window) = 0;

			virtual sf::FloatRect GetGlobalBounds() = 0;

		};
	}
}
