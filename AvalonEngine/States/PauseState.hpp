#pragma once
#include <iostream>
#include "State.hpp"
#include "../UI/Button.hpp"

namespace av 
{
    namespace state
    {

        class PauseState : public State 
        {
            public:
                PauseState();

                void Update(float timestep) override;
                void Render(sf::RenderWindow& l_window) override;
                void HandleInput(sf::Event l_event) override;

                bool m_exit_pause_ = false;
                bool m_exit_game_ = false;
                
            private:

            sf::Text m_title_;
            sf::Font m_font_;

            ui::Button m_continue_game_;
            ui::Button m_options_;
            ui::Button m_quit_game_;

            void HandleMouseClick(const sf::Vector2f l_mouse_position);

        };

    }
}