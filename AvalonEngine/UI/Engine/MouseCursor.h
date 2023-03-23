//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_MOUSECURSOR_H
#define AVALONENGINE_MOUSECURSOR_H


#include "SFML/Graphics.hpp"

namespace av
{

    class  MouseCursor
    {

    public:
        explicit MouseCursor(float l_scale = 0.5f, sf::String l_file_location = "Assets/Textures/cursor.png");

        void Render(sf::RenderWindow& l_window) const;

        sf::Vector2f GetCenterPosition() const;
        void SetPosition(const sf::Vector2f& l_position);

    private:
        sf::Texture m_texture_;
        sf::Sprite m_body_;
    };
}


#endif //AVALONENGINE_MOUSECURSOR_H
