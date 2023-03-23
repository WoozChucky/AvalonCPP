//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_MATH_H
#define AVALONENGINE_MATH_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>


namespace av
{
    class Math
    {
    public:
        static sf::Vector2f getCenterCoordinates(
                sf::Vector2f l_position,
                sf::Vector2f l_size,
                sf::FloatRect l_destination_obj);
    };
}


#endif //AVALONENGINE_MATH_H
