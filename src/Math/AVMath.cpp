#include "AVMath.h"

using namespace av;

sf::Vector2f AVMath::GetCenterCoordinates(
	const sf::Vector2f l_position,
	const sf::Vector2f l_size,
	const sf::FloatRect l_destinationObject)
{
	const auto x = l_position.x + (l_size.x - l_destinationObject.width) / 2;
	const auto y = l_position.y + l_size.y / 2 - l_destinationObject.height;

	return {x, y};
}

sf::Vector2f AVMath::GetCenterCoordinates(
	const sf::Vector2f l_windowSize, 
	const sf::FloatRect l_sourceObject)
{
	const auto x = l_windowSize.x / 2 - l_sourceObject.width / 2;
	const auto y = l_windowSize.y / 2 - l_sourceObject.height / 2;

	return { x, y };
}
