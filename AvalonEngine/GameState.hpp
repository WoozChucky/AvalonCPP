#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"

namespace av {

	class GameState
	{
	public:
		GameState();
		~GameState();

		void Update(float timestep);
		void Render(sf::RenderWindow& l_Window);
		void HandleInput();
	private:
		Player m_Player;
		std::vector<Enemy> m_Enemies;
	};

}
