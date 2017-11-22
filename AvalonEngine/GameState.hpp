#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include "Enemy.hpp"
#include "UI/Button.hpp"

namespace av {

	class GameState
	{
	public:
		GameState();
		~GameState();

		void Update(float timestep);
		void Render(sf::RenderWindow& l_window);
		void HandleInput();
	private:
		Player m_player_;
		std::vector<Enemy> m_enemies_;
		ui::Button temp;
	};

}
