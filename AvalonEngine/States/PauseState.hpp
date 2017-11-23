#pragma once
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
                ~PauseState();

                void Update(float timestep) override;
                void Render(sf::RenderWindow& l_window) override;
                void HandleInput(sf::Event l_event) override;
                
            private:

            
            sf::Text m_title_;

            ui::Button m_continue_game_;
            ui::Button m_options_;
            ui::Button m_quit_game_;

        };

    }
}