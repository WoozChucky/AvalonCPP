#pragma once

#include <SFML/Graphics.hpp>

#include "GraphicsComponent.h"

namespace av
{
	class Entity
	{
	public:
		Entity() = default;
		virtual ~Entity() = default;

		virtual void Update(float timestep) = 0;
		virtual void Render(sf::RenderWindow& l_window);

		virtual sf::FloatRect GetGlobalBounds();

	protected:

		GraphicsComponent* m_GraphicsComponent;
	};
}
