#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Enemy.hpp"
#include "../EngineUI/Utils/Math.hpp"
#include "../EngineUI/MouseCursor.hpp"

namespace av {

	namespace state {

		class GameState : public State
		{
		public:
			explicit GameState(const sf::Vector2f l_window_size);

			void Update(float timestep) override;
			void Render(sf::RenderWindow& l_window) override;
			void HandleInput(sf::Event l_event) override;

			bool m_requires_pause = false;

			void Restart();
		private:
			MouseCursor m_cursor_;

			entities::Player m_player_;
			std::vector<entities::Enemy> m_enemies_;

			void HandleCollision();
		};

	}
}
