#pragma once

#include "Level.hpp"

namespace av
{

    class Tutorial : public Level
    {
        public:
            explicit Tutorial();

            void Update(float timestep) override;
            void HandleInput(sf::Event& l_event) override;
            void Render(sf::RenderWindow& l_window) override;
            
            void Pause() override;
            void Resume() override;
            void Restart() override;

            void ResolveCollision(Player& l_player, Enemy& l_enemy) override;

        private:
            Player m_player_;

            std::vector<Enemy> m_enemies_;
    };

}