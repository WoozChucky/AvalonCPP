#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

namespace av
{

	enum TextAlignment : short
	{
		Left = 0xE,
		Right = 0xB,
		Center = 0xC
	};

	class UIElement
	{
	public:
		virtual void Update(float timestep = 0) = 0;
		virtual void Render(sf::RenderWindow& l_window) = 0;
		virtual sf::FloatRect GetGlobalBounds() = 0;
	
	protected:
		virtual ~UIElement() = default;
	};
}



