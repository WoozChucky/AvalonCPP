#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

namespace av
{
	class Animation
	{
	public:
		Animation();

		void AddFrame(sf::IntRect l_rect);
		void SetSpriteSheet(const sf::Texture& l_texture);
		const sf::Texture* GetSpriteSheet() const;
		std::size_t GetSize() const;
		const sf::IntRect& GetFrame(std::size_t n) const;

	private:
		std::vector<sf::IntRect> m_Frames;
		const sf::Texture* m_Texture;
	};
}



