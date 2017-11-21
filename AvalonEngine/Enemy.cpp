#include "Enemy.hpp"


av::Enemy::Enemy(const sf::Vector2f l_size, const av::Class l_class) 
	: m_body_(l_size), m_class_(l_class)
{
	//BODY
	m_body_.setOutlineThickness(2.f);
	m_body_.setOutlineColor(sf::Color::Black);

	//TODO(Nuno): Fix random spawn as it is the same on every lauch of the executable
	m_body_.setPosition(float(rand() % 700 + 50), float(rand() % 100));
	m_body_.setFillColor(sf::Color::Red);
}

av::Enemy::~Enemy()
{
}

void av::Enemy::Update(float timestep)
{

}


void av::Enemy::Render(sf::RenderWindow& l_window)
{
	l_window.draw(m_body_);
}
