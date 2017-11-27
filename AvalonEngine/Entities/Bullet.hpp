#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <chrono>

namespace av
{
	class Bullet : public sf::CircleShape
	{
	public:
		Bullet(sf::Vector2f l_position, float x_direction, float y_direction);
		~Bullet();

		bool Update(float timestep);

		sf::Vector2f getPosition() const;

		float Top() const;
		float Bottom() const;
		float Left() const;
		float Right() const;
		std::chrono::time_point<std::chrono::system_clock> GetSpawnTime() const;
		void IncreaseDamage(int l_damage);
		void DecreaseDamage(int l_damage);
		void SetDamage(int l_damage);
		int GetDamage() const;
		int m_damage;

	private:
		float m_velocity;
		std::chrono::time_point<std::chrono::system_clock> m_spawnTime;
		sf::Vector2f m_direction;
	};
}

