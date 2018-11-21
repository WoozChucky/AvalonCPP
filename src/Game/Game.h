#pragma once

#include <string>
#include <File.h>
#include <SFML/Graphics.hpp>
#include <State.h>
#include "MenuState.h"

namespace av
{
	class Game
	{
	public:
		explicit Game(fs::Configuration l_cfg, const std::string& l_window_title = "Avalon : The Beginning");

		void Run();

	private:
		void HandleInput();
		void Update(float timestep) const;
		void Render();
		
		void RestartClock();

		void Restart();
		void ChangeState(State* l_state);
		void PreviousState();

		void Exit();

		sf::RenderWindow m_Window;
		sf::Clock m_Clock;

		double m_Elapsed;

		MenuState m_MenuState;

		Subject<EventType::State> m_StateManager;
		State* m_CurrentState;
		State* m_PreviousState;
	};
}



