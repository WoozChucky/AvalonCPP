#pragma once

#include <SFML/Graphics.hpp>
#include <State.h>
#include "Level.h"

namespace av
{
	class GameState : public State
	{
	public:
		explicit GameState(sf::Vector2f l_windowSize);

		void Update(float timestep) override;
		void Render(sf::RenderWindow& l_window) override;
		void HandleInput(sf::Event& l_event) override;

		void Restart();

	private:

		void RestartCurrentLevel() const;

		sf::RectangleShape m_Background;
		sf::RectangleShape m_MinimapBackground;

		Level * m_CurrentLevel;
		Level * m_NextLevel;

		Subject<EventType::Level> m_LevelManager;
	};
}
