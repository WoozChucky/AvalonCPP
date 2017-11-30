#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "State.hpp"
#include "../Levels/Level.hpp"
#include "../EngineUI/MouseCursor.hpp"

namespace av {

	class GameState : public State
	{
	public:
		explicit GameState(const sf::Vector2f l_window_size);

		void Update(float timestep) override;
		void Render(sf::RenderWindow& l_window) override;
		void HandleInput(sf::Event& l_event) override;

		void Restart();
	private:
		MouseCursor m_cursor_;

		Level * m_current_level_;
		Level * m_next_level_;

		Subject<EventType::Level> m_level_manager_;

		void HandleCollision();

		void RestartCurrentLevel();
	};
}
