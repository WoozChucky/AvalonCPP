#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "State.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Enemy.hpp"
#include "../UI/Button.hpp"

namespace av {

	namespace state {

		class GameState : public State
		{
		public:
			GameState();
			~GameState();

			void Update(float timestep) override;
			void Render(sf::RenderWindow& l_window) override;
			void HandleInput() override;

			void Restart();
		private:
			entities::Player m_player_;
			std::vector<entities::Enemy> m_enemies_;
			ui::Button temp;
		};

	}
}