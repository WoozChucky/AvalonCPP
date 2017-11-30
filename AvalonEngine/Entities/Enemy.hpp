#pragma once

#include <SFML/Graphics.hpp>
#include "Class.hpp"
#include "../GameUI/Healthbar.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "../Components/GraphicsComponent.hpp"
//#include "../Components/AIComponent.hpp"
//#include "../Components/PhysicsComponent.hpp"

namespace av
{
	class Enemy : public Entity, public sf::RectangleShape
	{
	public:
		explicit Enemy(sf::Vector2f l_size, Class l_class);

		void Update(float timestep) override;
		void Render(sf::RenderWindow& l_window) override;
		void HandleInput(sf::Event l_event) override;
		bool Collide(Entity& l_entity) override;

		void setPosition(sf::Vector2f l_position);
		sf::Vector2f getPosition() const;
		sf::Vector2f getSize() const;
		RectangleShape getBody();
		
		bool IsAlive() override;
		bool Collide(Bullet& l_entity);
		bool Collide(Enemy l_entity);
		bool Collide(Player& l_entity) const;

		Healthbar GetHealthbar();
		RectangleShape GetBody();
		

	private:
		void TakeDamage(sf::Uint32 l_damage);

		RectangleShape m_body_;
		Healthbar m_healthbar_;
		Class m_class_;

		bool m_alive_;

		//Components
		av::GrapicsComponent* m_graphics_;
	};
}



