#pragma once
#include "UIElement.h"

#include <SFML/Graphics.hpp>

namespace av
{
	class Button : public UIElement
	{
	public:

		Button(sf::Vector2f l_size, sf::Vector2f l_position);

		Button(sf::Vector2f l_size, sf::Vector2f l_position,
			sf::Color l_button_color = sf::Color::Blue,
			sf::Color l_text_color = sf::Color::Black,
		       const sf::String& l_title = sf::String("Button"),
			sf::Uint32 l_text_size = 30);

		virtual ~Button() = default;

		void SetSize(sf::Vector2f l_size);
		void SetPosition(sf::Vector2f l_position);
		void SetFont(const sf::Font& l_font);
		void SetTextSize(sf::Uint32 l_size);
		void SetText(const sf::String& l_text);
		void SetTextColor(sf::Color l_color);
		void SetTextBackgroundColor(sf::Color l_color);
		void SetTextAlignment(TextAlignment l_alignment);

		void SetBackgroundColor(sf::Color l_color);
		void SetBackgroundOutlineColor(sf::Color l_color);
		void SetBackgroundOutlineThickness(float l_thickness);

		//Base class overrides
		void Update(float timestep) override;
		void Render(sf::RenderWindow& l_window) override;
		sf::FloatRect GetGlobalBounds() override;

	private:

		void Init(sf::Vector2f l_size, sf::Vector2f l_position,
			sf::Uint32 l_text_size, sf::Color l_button_color,
			sf::Color l_text_color, const sf::String& l_text);

		//Text
		sf::Text m_Text;
		sf::Font m_Font;

		// Body
		sf::RectangleShape m_Background;

		bool m_Inited;
	};
}



