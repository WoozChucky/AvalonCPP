#pragma once

#include <State.h>
#include <Button.h>
#include <SFML/Graphics.hpp>

namespace av
{
	class MenuState : public State
	{
	public:
		explicit MenuState(sf::Vector2f l_windowSize);

		void Update(float timestep) override;
		void Render(sf::RenderWindow& l_window) override;
		void HandleInput(sf::Event& l_event) override;

	private:
		Button m_NewGameButton;
		Button m_HighScoreButton;
		Button m_QuitGameButton;

		sf::RectangleShape m_Background;

		sf::Uint32 m_VirtualIndex = 0;

		void HandleArrowSelection(int l_direction);
		void HandleMouseClick(const sf::Vector2f& l_mouse_position);

		void InitializeUI();
	};
}



