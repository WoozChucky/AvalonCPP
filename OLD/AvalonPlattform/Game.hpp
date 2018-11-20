#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <FileSystem/File.h>
#include <Core/States/State.h>
#include <Core/States/MenuState.h>
#include <Core/States/PauseState.h>
#include <Core/States/GameState.h>

namespace av {

	class Game
	{
	public:
		explicit Game(fs::Configuration l_cfg, const std::string& window_title = "Avalon : The Beginning");

		void Run();
		

	private:
		//States
		State* m_current_state_;
		State* m_previous_state_;

		GameState m_game_state_;
		MenuState m_menu_state_;
		PauseState m_pause_state_;

		Subject<EventType::State> m_state_manager_;

		//SFML
		sf::RenderWindow m_window_;
		sf::Clock m_clock_;

		double m_elapsed_;

		void HandleInput();
		void Update(float timestep) const;
		void Render();
		void RestartClock();
		void Restart();
		void ChangeState(State* l_state);
		void Exit();
		void PreviousState();
	};

}
