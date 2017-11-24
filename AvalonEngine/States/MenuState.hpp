#pragma once
#include <iostream>
#include "State.hpp"
#include "../EngineUI/Button.hpp"

namespace av
{
	namespace state 
	{
		class MenuState : public State
		{
		public:
			MenuState();

			void Update(float timestep) override;
			void Render(sf::RenderWindow& l_window) override;		
			void HandleInput(sf::Event l_event) override;

			bool m_new;
			bool m_high;
			bool m_exit;

		private:

			ui::Button m_new_game_;
			ui::Button m_high_scores_;
			ui::Button m_quit_game_;
			sf::RectangleShape m_background_;

			sf::Uint32 m_virtual_index_ = 0;

			void HandleArrowSelection(int l_direction);
			void HandleMouseClick(const sf::Vector2f& l_mouse_position);
		};
	}
}


