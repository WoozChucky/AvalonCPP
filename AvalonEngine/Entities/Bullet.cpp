#include "Bullet.hpp"



Bullet::Bullet(const sf::Vector2f l_position, const float x_direction, const float y_direction) 
	: CircleShape(6), m_direction(x_direction, y_direction) {
	m_velocity = 450.f;
	setPosition(l_position);
	setOrigin(6, 6);
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(2.f);
	m_spawnTime = std::chrono::system_clock::now();
	m_damage = 30;
}

Bullet::~Bullet() {

}

bool Bullet::Update(const float timestep) {
	if (CircleShape::getPosition().y - m_velocity*timestep > 0 && CircleShape::getPosition().x - m_velocity*timestep > 0) {
		move(m_direction.x*m_velocity*timestep, m_direction.y*m_velocity*timestep);
		return true;
	}
	return false;
}

sf::Vector2f Bullet::getPosition() const
{
	return CircleShape::getPosition();
}

float Bullet::Top() const
{
	return getOrigin().y - getRadius();
}

float Bullet::Bottom() const
{
	return getOrigin().y + getRadius();
}

float Bullet::Left() const
{
	return getOrigin().x - getRadius();
}

float Bullet::Right() const
{
	return getOrigin().x + getRadius();
}

std::chrono::time_point<std::chrono::system_clock> Bullet::GetSpawnTime() const
{
	return m_spawnTime;
}

void Bullet::IncreaseDamage(const int l_damage) {
	m_damage += l_damage;
}

void Bullet::DecreaseDamage(const int l_damage) {
	m_damage -= l_damage;
}

void Bullet::SetDamage(const int l_damage) {
	m_damage = l_damage;
}

int Bullet::GetDamage() const
{
	return m_damage;
}
