#include "Entity.h"

using namespace av;

Entity::Entity(GraphicsComponent* l_graphicsComponent)
	: m_GraphicsComponent(l_graphicsComponent)
{

}

void Entity::Render(sf::RenderWindow& l_window)
{
	this->m_GraphicsComponent->Render(*this, l_window);
}

sf::FloatRect Entity::GetGlobalBounds()
{
	return this->getGlobalBounds();
}

float Entity::X()
{
	return this->getPosition().x;
}

float Entity::Y()
{
	return this->getPosition().y;
}
