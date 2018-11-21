#pragma once
#include "State.h"
#include "Button.h"

namespace av
{
	class PauseState : public State
	{
	public:

		explicit PauseState(sf::Vector2f l_windowSize);

		void Update(float timestep) override;
		void Render(sf::RenderWindow& l_window) override;
		void HandleInput(sf::Event& l_event) override;

	private:

		sf::Text m_TitleText;
		sf::Font m_Font;

		Button m_ContinueGameButton;
		Button m_OptionsButton;
		Button m_QuitGameButton;

		void HandleMouseClick(sf::Vector2f l_mouse_position);
		void InitializeUI();
	};
}


