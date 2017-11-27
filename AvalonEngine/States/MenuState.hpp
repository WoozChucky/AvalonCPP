#pragma once
#include <iostream>
#include "State.hpp"
#include "../EngineUI/Button.hpp"

#define BUTTON_MARGIN 25.f

namespace av
{
	class MenuState : public State
	{
	public:
		explicit MenuState(const sf::Vector2f l_window_size);

		void Update(float timestep) override;
		void Render(sf::RenderWindow& l_window) override;		
		void HandleInput(sf::Event l_event) override;

		bool m_new;
		bool m_high;
		bool m_exit;

	private:

		Button m_new_game_;
		Button m_high_scores_;
		Button m_quit_game_;
		sf::RectangleShape m_background_;

		sf::Uint32 m_virtual_index_ = 0;

		void HandleArrowSelection(int l_direction);
		void HandleMouseClick(const sf::Vector2f& l_mouse_position);

		void InitializeUI();
	};
}


