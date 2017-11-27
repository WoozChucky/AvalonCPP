#include "State.hpp"

av::State::State(const sf::Vector2f l_window_size)
{
	this->m_window_size_ = l_window_size;
}

sf::Vector2f av::State::GetWindowSize() const
{
	return this->m_window_size_;
}

void av::State::SetWindowSize(const sf::Vector2f l_window_size)
{
	this->m_window_size_ = l_window_size;
}
