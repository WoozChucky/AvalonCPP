#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.hpp"

namespace av {

	class Game
	{
	public:
		explicit Game(std::string window_title = "Avalon : The Beginning");
		~Game();

		void HandleInput();
		void Update(float timestep);
		void Render();
		void Run();
		void RestartClock();

		sf::RenderWindow* GetWindow();

	private:
		av::GameState m_game_state_;
		sf::RenderWindow m_window_;
		sf::Clock m_clock_;
		double m_elapsed_;
	};

}
