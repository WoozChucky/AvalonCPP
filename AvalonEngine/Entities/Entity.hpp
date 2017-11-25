#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::RectangleShape
{
public:
	Entity(const sf::Vector2f l_size)
	{
		this->setSize(l_size);
	}

	virtual void Update(float timsetep) = 0;
	virtual void Render(sf::RenderWindow& l_window) = 0;
	virtual void HandleInput(sf::Event l_event) = 0;
};

