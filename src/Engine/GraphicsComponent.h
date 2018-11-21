#pragma once

#include <SFML/Graphics.hpp>

namespace av
{
	class Entity;

	class GraphicsComponent
	{
	public:
		virtual ~GraphicsComponent() = default;
		virtual void Render(Entity& l_entity, sf::RenderWindow& l_window);
	};

}