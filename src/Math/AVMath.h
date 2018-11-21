#pragma once

#include <SFML/Graphics.hpp>

namespace av
{
	class AVMath
	{
	public:
		static sf::Vector2f GetCenterCoordinates(sf::Vector2f l_position, sf::Vector2f l_size, sf::FloatRect l_destinationObject);

		static sf::Vector2f GetCenterCoordinates(sf::Vector2f l_windowSize, sf::FloatRect l_sourceObject);
	};
}
