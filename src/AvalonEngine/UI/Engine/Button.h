//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_BUTTON_H
#define AVALONENGINE_BUTTON_H

#include <SFML/Graphics.hpp>
#include "Events/MouseEvents.h"
#include "UIElement.h"

namespace av {

    class Button : public UIElement {

    public:

        Button(sf::Vector2f l_size, sf::Vector2f l_position);

        Button(sf::Vector2f l_size, sf::Vector2f l_position,
               sf::Color l_button_color = sf::Color::Blue,
               sf::Color l_text_color = sf::Color::Black,
               sf::String l_title = sf::String("Button"),
               sf::Uint32 l_text_size = 30);

        virtual ~Button() = default;

        void SetSize(sf::Vector2f l_size);
        void SetPosition(sf::Vector2f l_position);
        void SetFont(sf::Font l_font);
        void SetTextSize(sf::Uint32 l_size);
        void SetText(sf::String l_text);
        void SetTextColor(sf::Color l_color);
        void SetTextBackgroundColor(sf::Color l_color);
        void SetTextAlignment(TextAlignment l_alignment);

        void SetBackgroundColor(sf::Color l_color);
        void SetBackgroundOutlineColor(sf::Color l_color);
        void SetBackgroundOutlineThickness(float l_thickness);

        void SetOnClick(MouseClickCallback* l_callback);
        void SetOnMouseEnter(MouseOverEnterCallback* l_callback);
        void SetOnMouseExit(MouseOverExitCallback* l_callback);
        void OnClick() const;

        //Base class overrides
        void Update(float timestep) override;
        void Render(sf::RenderWindow& l_window) override;
        sf::FloatRect GetGlobalBounds() override;

    private:
        void Init(sf::Vector2f l_size, sf::Vector2f l_position,
                  sf::Uint32 l_text_size, sf::Color l_button_color,
                  sf::Color l_text_color, sf::String l_text);

        //Events
        MouseClickCallback* m_click_callback_;
        MouseOverEnterCallback* m_enter_callback_;
        MouseOverExitCallback* m_exit_callback_;

        //Text
        sf::Text m_text_;
        sf::Font m_font_;

        // Body
        sf::RectangleShape m_background_;

        bool m_inited_;

    };
}


#endif //AVALONENGINE_BUTTON_H
