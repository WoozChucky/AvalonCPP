#pragma once

#include <SFML/Graphics.hpp>

#include "GraphicsComponent.h"

namespace av
{
	class Entity : public sf::Shape
	{
	public:
		Entity(GraphicsComponent* l_graphicsComponent);
		virtual ~Entity() = default;

		virtual void Update(float timestep) = 0;

		virtual void Render(sf::RenderWindow& l_window);

		virtual sf::FloatRect GetGlobalBounds();
		virtual float X();
		virtual float Y();

	protected:

		GraphicsComponent* m_GraphicsComponent;
	};
}
