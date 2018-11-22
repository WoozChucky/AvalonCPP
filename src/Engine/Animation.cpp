#include "Animation.h"

using namespace av;

Animation::Animation()
	: m_Texture(nullptr)
{
}

void Animation::AddFrame(sf::IntRect l_rect)
{
	this->m_Frames.push_back(l_rect);
}

void Animation::SetSpriteSheet(const sf::Texture& l_texture)
{
	this->m_Texture = &l_texture;
}

const sf::Texture* Animation::GetSpriteSheet() const
{
	return this->m_Texture;
}

std::size_t Animation::GetSize() const
{
	return this->m_Frames.size();
}

const sf::IntRect& Animation::GetFrame(std::size_t n) const
{
	return this->m_Frames[n];
}





