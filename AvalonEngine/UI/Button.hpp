#pragma once

#include <SFML/Graphics.hpp>
#include "Events/MouseEvents.hpp"
#include "UIElement.hpp"

namespace av {

	namespace ui
	{

		class Button : public UIElement {

		public:
			
			Button(sf::Vector2f l_size, sf::Vector2f l_position, 
				sf::String l_title = sf::String("Button"));
			virtual ~Button() = default;

			void setFont(sf::Font l_font);
			void setTextSize(Uint32 l_size);
			void setText(sf::String l_text);
			void setTextColor(sf::Color l_color);
			void setTextBackgroundColor(sf::Color l_color);

			void setBackgroundColor();
			void setBackgroundOutlineColor();
			void setBackgroundOutlineThickness();

			void setOnClick(events::MouseClickCallback* l_callback);
			void setOnMouseEnter(events::MouseOverEnterCallback* l_callback);
			void setOnMouseExit(events::MouseOverExitCallback* l_callback);
			void onClick() const;

			//Base class overrides
			void Update(float timestep) override;
			void Render(sf::RenderWindow& l_window) override;
			sf::FloatRect GetGlobalBounds() override;

		private:
			void Init();

			//Events
			events::MouseClickCallback* m_click_callback_;
			events::MouseOverEnterCallback* m_enter_callback_;
			events::MouseOverExitCallback* m_exit_callback_;

			//Text
			sf::Text m_text_;
			sf::Font m_font_;

			// Body
			sf::RectangleShape m_background_;

			// Colors
			sf::Color m_textColor_;
			sf::Color m_OutlineColor_;
			sf::Color m_backgroundColor_;

		};
	}
}
