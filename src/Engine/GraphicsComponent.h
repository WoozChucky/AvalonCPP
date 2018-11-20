#pragma once

#include "Entity.h"

namespace av
{

	class GraphicsComponent
	{
	public:
		virtual ~GraphicsComponent() = default;
		virtual void Render(Entity& l_entity, sf::RenderWindow& l_window) = 0;
	};

}