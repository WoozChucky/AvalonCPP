#include "Player.hpp"
#include "../Locator.hpp"

av::Player::Player() : 
	Entity(), CircleShape(40, 3), m_rifle_(sf::Vector2f(14.f, 45.f))
{
	this->m_player_velocity_ = 200.f;
	this->m_velocity_ = {m_player_velocity_, m_player_velocity_};
	this->setPosition(sf::Vector2f(400.f, 550.f));
	this->setFillColor(sf::Color(48, 48, 48));
	this->setOrigin(40, 40);
	this->setOutlineColor(sf::Color::Black);
	this->setOutlineThickness(2.0f);
	this->m_spawn_time_ = std::chrono::system_clock::now();
	this->m_side_distance_ = sqrt(pow(CircleShape::getPoint(0).x - CircleShape::getPoint(1).x, 2) + pow(CircleShape::getPoint(0).y - CircleShape::getPoint(1).y, 2));

	//Rifle setup
	this->m_rifle_.setOrigin(sf::Vector2f(7.f, 45.f));
	this->m_rifle_.setFillColor(sf::Color::White);
	this->m_rifle_.setOutlineColor(sf::Color::Black);
	this->m_rifle_.setOutlineThickness(2.f);
	this->m_rifle_.setPosition(this->getPosition());
}

void av::Player::Update(const float timestep)
{
	this->Move(timestep);

	auto angle = getRotationAngle();
 
	//Lock rifle rotation
	if(angle >= -90.1f && angle <= 90.1f)
	{
		this->m_rifle_.setRotation(angle);
	}

	this->Shoot(timestep);
}

void av::Player::Render(sf::RenderWindow& l_window)
{
	l_window.draw(*this);
	l_window.draw(this->m_rifle_);
	for (auto i = 0; i < m_bullets.size(); i++) {
		l_window.draw(this->m_bullets[i]);
	}
}

void av::Player::HandleInput(const sf::Event l_event)
{
	//Update mouse position
	if (l_event.type == sf::Event::EventType::MouseMoved) {

		this->m_mouse_position_ = sf::Vector2f(l_event.mouseMove.x, l_event.mouseMove.y);

	}
	else if (l_event.type == sf::Event::EventType::KeyPressed) //NOTE: This is used for testing purposes.
	{
		if(l_event.key.code == sf::Keyboard::Key::Space)
		{
			av::Locator::GetAudio().PlaySFX(audio::SFX::RIFLE_SHOOT_NORMAL);
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

void av::Player::Move(const float timestep)
{
	// we move the player and the rifle accordingly based on the buttons pressed
    sf::CircleShape::move(m_velocity_.x*timestep,m_velocity_.y*timestep);
    this->m_rifle_.move(m_velocity_.x*timestep,m_velocity_.y*timestep);
    if ((Right() < 800) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))){
        m_velocity_.x = m_player_velocity_;
        if ((Left() > 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))){
            m_velocity_.x = 0;
        } /* else if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))) {
            m_velocity_.y = -m_player_velocity_;
        } else if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))){
            m_velocity_.y = m_player_velocity_;
        } */ else {
            m_velocity_.y = 0;
        }
    } else if ((Left() > 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))) {
        m_velocity_.x = -m_player_velocity_;
        if ((Right() < 800) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))){
            m_velocity_.x = 0;
        } /* else if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))) {
            m_velocity_.y = -m_player_velocity_;
        } else if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))){
            m_velocity_.y = m_player_velocity_;
        } */ else {
            m_velocity_.y = 0;
        }
    } 
	/*
	else if ((Top() > 0 && Top() < 400) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))){
        m_velocity_.y = -m_player_velocity_;
        if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))){
            m_velocity_.y = 0;
        } else if ((Right() < 800) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))){
            m_velocity_.x = m_player_velocity_;
        } else if( (Left() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))) {
            m_velocity_.x = -m_player_velocity_;
        } else {
            m_velocity_.x = 0;
        }
    } else if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))){
        m_velocity_.y = m_player_velocity_;
        if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))){
            m_velocity_.y = 0;
        } else if ((Right() < 800) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))){
            m_velocity_.x = m_player_velocity_;
        } else if( (Left() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))) {
            m_velocity_.x = -m_player_velocity_;
        } else {
            m_velocity_.x = 0;
        }
    }*/ else {
        m_velocity_.x = 0.f;
        m_velocity_.y = 0.f;
    }
}


void av::Player::Shoot(const float timestep) {
	// we shoot bullets every .3 seconds
	// we have a timer on the last spawned bullet that we can check
	// if we do not have any bullets, then we use the timer present in this class
	// to keep the direction of the bullets in its class, we have a direction member
	// that is basically calculating the vector representing the direction of the rifle and then
	// we normalize it
	// NOTE : perhaps change the SQRT function with something more efficient ?
	const auto ms = std::chrono::system_clock::now();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		
		const auto l_position{ getBulletSpawn() };

		const auto magnitude{ sqrt(pow((l_position.x - this->m_rifle_.getPosition().x),2) + pow((l_position.y - this->m_rifle_.getPosition().y),2)) };

		const auto x_direction{ (l_position.x - this->m_rifle_.getPosition().x) / magnitude };
		const auto y_direction{ (l_position.y - this->m_rifle_.getPosition().y) / magnitude };

		if ((!m_bullets.empty()) && (std::chrono::duration_cast<std::chrono::milliseconds>(ms - m_bullets[m_bullets.size() - 1].GetSpawnTime()).count() > 300)) {
			Bullet bullet(l_position, x_direction, y_direction);
			this->m_spawn_time_ = bullet.GetSpawnTime();
			m_bullets.push_back(bullet);

			// Play Shoot SFX
			Locator::GetAudio().PlaySFX(audio::SFX::RIFLE_SHOOT_NORMAL);
		}
		else if (std::chrono::duration_cast<std::chrono::milliseconds>(ms - this->m_spawn_time_).count() > 300) {
			Bullet bullet(l_position, x_direction, y_direction);
			m_bullets.push_back(bullet);
			this->m_spawn_time_ = bullet.GetSpawnTime();

			// Play Shoot SFX
			Locator::GetAudio().PlaySFX(audio::SFX::RIFLE_SHOOT_NORMAL);
		}
	}
	// This loop clears the bullets list if there are any buillets that 
	// have hit an enemy or out of window
	for (auto i = 0; i < m_bullets.size(); i++) {
		const auto temp = m_bullets[i].Update(timestep);
		if (!temp) {
			m_bullets.erase(m_bullets.begin() + i);
		}
	}
}

float av::Player::x() const
{
	return this->getPosition().x;
}

float av::Player::y() const
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
	return this->getPosition().y + 0.5 * this->getRadius();
}

float av::Player::getRotationAngle() const
{
	// This function gets the rotation angle that helps us track the mouse position with the gun
	// Explanation : 
	//                  RP - angle at mouse position
	//   |\      |      K - Axis of rotation of our gun
	//   | \     |      RK = RP (K || P) - Angle that we want to rotate our gun
	//   |  \ R  |      P = My - Gy
	// P |   \   |  K   Q = Gx - Mx
	//   |    \  |      Solution : RP = RK = atan(Q/P)
	//   |     \ |      We could try asin and acos (and I did), but I believe that because of the RANGE
	//   |______\|      of these functions we are not getting the correct result. Might be wrong though
	//      Q
	// 
	// 
	return atan2(this->m_rifle_.getPosition().y - this->m_mouse_position_.y, this->m_rifle_.getPosition().x - this->m_mouse_position_.x)*180.f / 3.1428 - 90;
}

sf::Vector2f av::Player::getBulletSpawn() const
{
	const auto x{ static_cast<float>(this->m_rifle_.getPosition().x + this->m_rifle_.getSize().y * sin(
		this->m_rifle_.getRotation() * 3.1428 / 180)) };

	const auto y{ static_cast<float>(this->m_rifle_.getPosition().y - this->m_rifle_.getSize().y * sin(
		(90 - this->m_rifle_.getRotation()) * 3.1428 / 180)) };

	return sf::Vector2f(x, y);
}

void av::Player::Restart() {
	this->m_bullets.clear();
	this->m_rifle_.setPosition(400.f, 550.f);
	this->setPosition(400.f, 550.f);
}

