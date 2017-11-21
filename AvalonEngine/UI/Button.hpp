#pragma once

#include <SFML/Graphics.hpp>

namespace av::ui {

    class Button {

        public:
            Button(sf:Vector2f l_button_size, sf::Vector2f l_text_size);

            void setText(std::string text);
            void setOnClick(void (* callback)());
        private:

            sf::String m_text_;
            
            // Body
            sf::RectangleShape m_body_;
            
            // Colors
            sf::Color m_textColor_;
            sf::Color m_OutlineColor_;
            sf::Color m_backgroundColor_;

    };

}