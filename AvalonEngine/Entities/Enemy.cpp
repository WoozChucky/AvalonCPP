#include "Enemy.hpp"


av::entities::Enemy::Enemy(const sf::Vector2f l_size, const Class l_class)
	: m_body_(l_size), m_healthbar_(sf::Vector2f(- 500.f, - 500.f)), m_class_(l_class), m_alive_(true)
{
	//BODY
	this->m_body_.setOutlineThickness(2.f);
	this->m_body_.setOutlineColor(sf::Color::Black);

	//TODO: Think of a better approach for enemy spawning
	this->m_body_.setPosition(static_cast<float>(rand() % 690 + 50), static_cast<float>(rand() % 100));
	this->m_body_.setFillColor(sf::Color::Red);

	//HEALTHBAR
	this->m_healthbar_.setPosition(this->m_body_.getPosition());
}

void av::entities::Enemy::Update(float timestep)
{

}

void av::entities::Enemy::Render(sf::RenderWindow& l_window)
{
	this->m_healthbar_.Render(l_window);
	l_window.draw(this->m_body_);
}

sf::Vector2f av::entities::Enemy::getPosition() const
{
	return this->m_body_.getPosition();
}

sf::Vector2f av::entities::Enemy::getSize() const
{
	return this->m_body_.getSize();
}

void av::entities::Enemy::TakeDamage(const sf::Uint32 l_damage)
{
	//NOTE: This is where aditional combat logic should go before the Healthbar->Minus().

	this->m_alive_ = this->m_healthbar_.Minus(l_damage);
}

bool av::entities::Enemy::Collide(Player& l_entity) const
{
	//TODO
	return false;
}

bool av::entities::Enemy::Collide(Bullet& l_entity)
{
	if ( l_entity.getGlobalBounds().left > getPosition().x && getPosition().x + getSize().x > l_entity.getGlobalBounds().left ||
        l_entity.getGlobalBounds().left + l_entity.getGlobalBounds().width > getPosition().x && getPosition().x + getSize().x > l_entity.getGlobalBounds().left + l_entity.getGlobalBounds().width) {
            if (getPosition().y < l_entity.getGlobalBounds().top && getPosition().y + getSize().y > l_entity.getGlobalBounds().top){
                TakeDamage(l_entity.GetDamage());
                return true;
            }
        }
    return false;
}

bool av::entities::Enemy::IsAlive() const
{
    return this->m_alive_;
}
