//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_PAUSESTATE_H
#define AVALONENGINE_PAUSESTATE_H


#include "State.h"
#include "../../UI/Engine/Button.h"

namespace av
{

    class PauseState : public State
    {
    public:
        explicit PauseState(sf::Vector2f l_window_size);

        void Update(float timestep) override;
        void Render(sf::RenderWindow& l_window) override;
        void HandleInput(sf::Event& l_event) override;

    private:

        sf::Text m_title_;
        sf::Font m_font_;

        Button m_continue_game_;
        Button m_options_;
        Button m_quit_game_;

        void HandleMouseClick(sf::Vector2f l_mouse_position);
        void InitializeUI();
    };
}


#endif //AVALONENGINE_PAUSESTATE_H
