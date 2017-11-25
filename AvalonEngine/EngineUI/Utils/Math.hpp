#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace av
{
	namespace ui
	{
		namespace utils
		{
			class Math
			{
			public:
				static sf::Vector2f getCenterCoordinates(
					sf::Vector2f l_position,
					sf::Vector2f l_size,
					sf::FloatRect l_destination_obj);
			};
		}
	}
}



