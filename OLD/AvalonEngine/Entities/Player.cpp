//
// Created by Nuno Levezinho on 07/02/2018.
//

#include <cmath>
#include "Player.h"
#include "../Locator.h"
#include "Components/Graphics/PlayerGraphicsComponent.h"
#include "Components/Input/PlayerInputComponent.h"

av::Player::Player() :
        Entity(), CircleShape(40, 3), m_rifle_(sf::Vector2f(14.f, 45.f))
{
    //Components setup
    this->m_graphics_ = new PlayerGraphicsComponent();
    this->m_input_ = new PlayerInputComponent();

    this->m_player_velocity_ = 200.f;
    this->m_velocity_ = { m_player_velocity_ , m_player_velocity_};
    this->setPosition(sf::Vector2f(400.f, 550.f));
    this->setFillColor(sf::Color(48, 48, 48));
    this->setOrigin(40, 40);
    this->setOutlineColor(sf::Color::Black);
    this->setOutlineThickness(2.0f);
    this->m_spawn_time_ = std::chrono::system_clock::now();
    this->m_side_distance_ = static_cast<float>(sqrt(pow(CircleShape::getPoint(0).x - CircleShape::getPoint(1).x, 2) + pow(CircleShape::getPoint(0).y - CircleShape::getPoint(1).y, 2)));

    //Rifle setup
    this->m_rifle_.setOrigin(sf::Vector2f(7.f, 45.f));
    this->m_rifle_.setFillColor(sf::Color::White);
    this->m_rifle_.setOutlineColor(sf::Color::Black);
    this->m_rifle_.setOutlineThickness(2.f);
    this->m_rifle_.setPosition(this->getPosition());
}

void av::Player::Update(const float timestep)
{
    this->m_input_->Update(*this, timestep);
}

void av::Player::Render(sf::RenderWindow& l_window)
{
    this->m_graphics_->Render(*this, l_window);
}

void av::Player::HandleInput(const sf::Event l_event)
{
    //Update mouse position
    if (l_event.type == sf::Event::EventType::MouseMoved) {

        this->m_mouse_position_ = sf::Vector2f(l_event.mouseMove.x, l_event.mouseMove.y);

    }

    if (l_event.type == sf::Event::EventType::KeyPressed) //NOTE: This is used for testing purposes.
    {
        if(l_event.key.code == sf::Keyboard::Key::Space)
        {
            av::Locator::GetAudio().PlaySFX(audio::SFX::RIFLE_SHOOT_NORMAL, false);
        }
    }

}

bool av::Player::IsAlive()
{
    return true;
}

bool av::Player::Collide(Entity& l_entity)
{
    return false;
}

float av::Player::X() const
{
    return this->getPosition().x;
}

float av::Player::Y() const
{
    return this->getPosition().y;
}

float av::Player::Left() const
{
    return this->getPosition().x - this->m_side_distance_ / 2;
}

float av::Player::Right() const
{
    return this->getPosition().x + this->m_side_distance_ / 2;
}

float av::Player::Top() const
{
    return this->getPosition().y - this->getRadius();
}

float av::Player::Bottom() const
{
    return static_cast<float>(this->getPosition().y + 0.5 * this->getRadius());
}

std::vector<av::Bullet> av::Player::GetBullets() const
{
    return this->m_bullets_;
}

sf::RectangleShape av::Player::GetRifle() const
{
    return this->m_rifle_;
}

void av::Player::Restart() {
    this->m_bullets_.clear();
    this->m_rifle_.setPosition(400.f, 550.f);
    this->setPosition(400.f, 550.f);
}

sf::FloatRect av::Player::GetGlobalBounds() {
    return sf::FloatRect();
}

sf::RectangleShape& av::Player::getRifle() {
    return this->m_rifle_;
}

void av::Player::setRifle(const sf::RectangleShape l_rifle) {
    this->m_rifle_ = l_rifle;
}

sf::Vector2f& av::Player::getVelocity() {
    return this->m_velocity_;
}

void av::Player::setVelocity(const sf::Vector2f l_velocity) {
    this->m_velocity_ = l_velocity;
}

float av::Player::getPlayerVelocity() const {
    return this->m_player_velocity_;
}

void av::Player::setPlayerVelocity(const float l_velocity) {
    this->m_player_velocity_ = l_velocity;
}

std::chrono::time_point<std::chrono::system_clock> av::Player::getSpawnTime() const {
    return this->m_spawn_time_;
}

void av::Player::setSpawnTime(const std::chrono::time_point<std::chrono::system_clock> l_time) {
    this->m_spawn_time_ = l_time;
}

std::vector<av::Bullet> &av::Player::getBullets() {
    return this->m_bullets_;
}
