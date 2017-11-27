#pragma once

#include <typeinfo>
#include <SFML/Graphics.hpp>
#include "States/State.hpp"
#include "States/GameState.hpp"
#include "States/MenuState.hpp"
#include "States/PauseState.hpp"

namespace av {

	class Game
	{
	public:
		explicit Game(sf::Uint32 l_width, sf::Uint32 l_height, std::string window_title = "Avalon : The Beginning");

		void HandleInput();
		void Update(float timestep);
		void Render();
		void Run();
		void RestartClock();
		void Restart();

		void ChangeState(state::State* l_state);

	private:
		//States
		state::State* m_current_state_;
		state::State* m_previous_state_;

		state::GameState m_game_state_;
		state::MenuState m_menu_state_;
		state::PauseState m_pause_state_;

		//SFML
		sf::RenderWindow m_window_;
		sf::Clock m_clock_;

		double m_elapsed_;
	};

}
