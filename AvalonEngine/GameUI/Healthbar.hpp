#pragma once

#include <SFML/Graphics.hpp>

namespace av
{
    class Healthbar 
    {
    public:
        explicit Healthbar(sf::Vector2f l_position);

        void Update(float timestep) const;
        void Render(sf::RenderWindow& l_window) const;

        void SetPosition(sf::Vector2f l_position);

        bool Minus(sf::Uint32 l_damage);

    private:
        //NOTE: Check pros and cons of initializing vars in different ways
        static constexpr float HP_WIDTH = { 50.f };
        static constexpr float HP_HEIGHT = { 7.f };

        sf::RectangleShape m_current_health_;
        sf::RectangleShape m_missing_health_;

        int m_health_;

    };
}