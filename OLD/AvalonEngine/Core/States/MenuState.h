//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_MENUSTATE_H
#define AVALONENGINE_MENUSTATE_H


#include "State.h"
#include "../../UI/Engine/Button.h"

namespace av
{
    class MenuState : public State
    {
    public:
        explicit MenuState(sf::Vector2f l_window_size);

        void Update(float timestep) override;
        void Render(sf::RenderWindow& l_window) override;
        void HandleInput(sf::Event& l_event) override;

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


#endif //AVALONENGINE_MENUSTATE_H
