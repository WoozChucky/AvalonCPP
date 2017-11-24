#pragma once

#include <SFML/Graphics.hpp>

namespace av
{
    namespace ui
    {
        class Healthbar 
        {
        public:
            Healthbar(sf::Vector2f l_position);

            void Update(float timestep);
            void Render(sf::RenderWindow& l_window);

            void setPosition(sf::Vector2f l_position);

            bool Minus(sf::Uint32 l_damage);

            //NOTE: Check pros and cons of initializing vars in different ways
            static constexpr float HP_WIDTH = {50.f};
            static constexpr float HP_HEIGHT = {7.f};

        private:

            sf::RectangleShape m_current_health_;
            sf::RectangleShape m_missing_health_;

            int m_health_;

        };
    }
}