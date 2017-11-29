#pragma once

#include <SFML/Graphics.hpp>

namespace av {

	class Entity
	{
	public:
		Entity() {};
		virtual ~Entity() {};

		virtual void Update(float timestep) = 0;
		virtual void Render(sf::RenderWindow& l_window) = 0;
		virtual void HandleInput(sf::Event l_event) = 0;

		virtual bool IsAlive() = 0;
		virtual bool Collide(Entity& l_entity) = 0;

	};

}