#pragma once
#include "State.hpp"
#include "../UI/Button.hpp"

namespace av
{
	class MenuState : public State
	{
	public:
		MenuState();
		~MenuState();

		void Update(float timestep, sf::RenderWindow& l_window) override;
		void Render(sf::RenderWindow& l_window) override;
		void HandleInput() override;

		// Getters and Setters

		void setPressed(bool l_status);
		bool getPressed();

		void setMousePosition(const sf::Vector2i l_position);
		sf::Vector2i getMousePosition();

		void setButtonPressed(int l_index);
		int getButtonPressed(int l_index);
		
	private:

		ui::Button m_new_game_;
		ui::Button m_high_scores_;
		ui::Button m_quit_game_;
		sf::RectangleShape m_background_;

		bool m_pressed_;
		sf::Vector2i m_mouse_position_;
		int m_button_pressed_[3];
	};
}


