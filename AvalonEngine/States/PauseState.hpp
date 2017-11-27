#pragma once
#include <iostream>
#include "State.hpp"
#include "../EngineUI/Button.hpp"

namespace av 
{

    class PauseState : public State 
    {
        public:
            explicit PauseState(const sf::Vector2f l_window_size);

            void Update(float timestep) override;
            void Render(sf::RenderWindow& l_window) override;
            void HandleInput(sf::Event l_event) override;

            bool m_exit_pause_ = false;
            bool m_exit_game_ = false;
            bool m_options_over = false;
            
        private:

        sf::Text m_title_;
        sf::Font m_font_;

        Button m_continue_game_;
        Button m_options_;
        Button m_quit_game_;

        void HandleMouseClick(const sf::Vector2f l_mouse_position);
        void InitializeUI();
    };
}