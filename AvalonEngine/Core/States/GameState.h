//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_GAMESTATE_H
#define AVALONENGINE_GAMESTATE_H


#include "State.h"
#include "../../UI/Engine/MouseCursor.h"
#include "../Levels/Level.h"

namespace av {

    class GameState : public State
    {
    public:
        explicit GameState(sf::Vector2f l_window_size);

        void Update(float timestep) override;
        void Render(sf::RenderWindow& l_window) override;
        void HandleInput(sf::Event& l_event) override;

        void Restart();
    private:
        MouseCursor m_cursor_;

        Level * m_current_level_;
        Level * m_next_level_;

        Subject<EventType::Level> m_level_manager_;

        void HandleCollision();

        void RestartCurrentLevel();
    };
}


#endif //AVALONENGINE_GAMESTATE_H
