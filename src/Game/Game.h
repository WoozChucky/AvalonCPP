#pragma once

#include <string>
#include <File.h>
#include <SFML/Graphics.hpp>
#include <State.h>
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"

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
		sf::View m_DebugView;
		sf::Clock m_Clock;

		double m_Elapsed;

		MenuState m_MenuState;
		GameState m_GameState;
		PauseState m_PauseState;

		Subject<EventType::State> m_StateManager;
		State* m_CurrentState;
		State* m_PreviousState;

		sf::Image m_AppIcon;
	};
}



