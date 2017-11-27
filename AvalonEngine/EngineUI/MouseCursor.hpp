#pragma once

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