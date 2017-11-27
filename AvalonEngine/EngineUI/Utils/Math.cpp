#include "Math.hpp"

sf::Vector2f av::Math::getCenterCoordinates(
	const sf::Vector2f l_position,
	const sf::Vector2f l_size,
	const sf::FloatRect l_destination_obj)
{
	const auto x = l_position.x + (l_size.x - l_destination_obj.width) / 2;
	const auto y = l_position.y + l_size.y / 2 - l_destination_obj.height;

	return sf::Vector2f(x, y);
}