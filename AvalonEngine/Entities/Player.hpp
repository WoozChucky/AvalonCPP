#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <chrono>
#include "Entity.hpp"
#include "../Components/GraphicsComponent.hpp"
#include "../Components/InputComponent.hpp"
#include "../Components/PhysicsComponent.hpp"
#include "Bullet.hpp"

namespace av
{
	class Player : public Entity, public sf::CircleShape
	{
	public:
		Player(av::GrapicsComponent * l_graphics);

		void Update(float timestep) override;
		void Render(sf::RenderWindow& l_window) override;
		void HandleInput(sf::Event l_event) override;
		bool IsAlive() override;
		bool Collide(av::Entity& l_entity) override;

		
		void Restart();
		sf::Vector2f getBulletSpawn() const;

		std::vector<Bullet> m_bullets;

		sf::RectangleShape m_rifle_;

	private:
		sf::Vector2f m_mouse_position_;
		sf::Vector2f m_velocity_;
		float m_player_velocity_;
		// timer for the bullet spawn 
		std::chrono::time_point<std::chrono::system_clock> m_spawn_time_;
		// side size to render it properly
		float m_side_distance_;
		

		float x() const;
		float y() const;
		float Left() const;
		float Right() const;
		float Top() const;
		float Bottom() const;
		void Move(float timestep);
		void Shoot(float timestep);
		float getRotationAngle() const;

		//Components
		av::GrapicsComponent* 	m_graphics_;
		av::InputComponent* 	m_input_;
		av::PhysicsComponent*	m_physics_;
	};

}



