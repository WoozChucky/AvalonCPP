//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_UIELEMENT_H
#define AVALONENGINE_UIELEMENT_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace av
{

    enum TextAlignment : short {
        Left = 0xE,
        Right = 0xB,
        Center = 0xC
    };

    class UIElement
    {
    protected:
        virtual ~UIElement() = default;

    public:

        virtual void Update(float timestep) = 0;

        virtual void Render(sf::RenderWindow& l_window) = 0;

        virtual sf::FloatRect GetGlobalBounds() = 0;

    };

}

#endif //AVALONENGINE_UIELEMENT_H
