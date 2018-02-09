//
// Created by Nuno Levezinho on 07/02/2018.
//

#include <cmath>
#include "PlayerInputComponent.h"
#include "../../../Locator.h"

#define PI 3.14159265358979323846  /* pi */

av::PlayerInputComponent::PlayerInputComponent() = default;

void av::PlayerInputComponent::Update(av::Entity &l_entity, float timestep) {

    auto &player = dynamic_cast<Player&>(l_entity);

    Move(player, timestep);

    auto angle = GetRotationAngle(player);

    //Lock rifle rotation
    if(angle >= -90.1f && angle <= 90.1f)
    {
        player.getRifle().setRotation(angle);
    }

    Shoot(player, timestep);
}

void av::PlayerInputComponent::Move(Player& player, float timestep) {

    //The main reason for this spaguetti code, besides the fact that i'm an awful developer,
    //is that in a near future I plan on allowing the player to move in the Y axis.
    //So I am leaving that commented code here for future reference of that not to do, LOL.

    // we move the player based on the keyboard buttons pressed
    player.sf::CircleShape::move(player.getVelocity().x * timestep, player.getVelocity().y * timestep);
    player.getRifle().move(player.getVelocity().x * timestep, player.getVelocity().y * timestep);

    if ((player.Right() < 800) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))){
        player.getVelocity().x = player.getPlayerVelocity();

        if ((player.Left() > 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))){
            player.getVelocity().x = 0;
        } /* else if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))) {
            m_velocity_.y = -m_player_velocity_;
        } else if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))){
            m_velocity_.y = m_player_velocity_;
        } */ else {
            player.getVelocity().y = 0;
        }
    } else if ((player.Left() > 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))) {
        player.getVelocity().x = -player.getPlayerVelocity();

        if ((player.Right() < 800) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))){
            player.getVelocity().x = 0;
        } /* else if ((Top() > 0) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))) {
            m_velocity_.y = -m_player_velocity_;
        } else if ((Bottom() < 600) and (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))){
            m_velocity_.y = m_player_velocity_;
        } */ else {
            player.getVelocity().y = 0;
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
        player.getVelocity().x = 0.f;
        player.getVelocity().y = 0.f;
    }

}

void av::PlayerInputComponent::Shoot(Player& player, const float timestep) {
    // we shoot bullets every .3 seconds
    // we have a timer on the last spawned bullet that we can check
    // if we do not have any bullets, then we use the timer present in this class
    // to keep the direction of the bullets in its class, we have a direction member
    // that is basically calculating the vector representing the direction of the rifle and then
    // we normalize it
    // NOTE : perhaps change the SQRT function with something more efficient ?
    const auto ms = std::chrono::system_clock::now();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

        const auto l_position{ GetBulletSpawn(player) };

        const auto magnitude{ sqrt(pow((l_position.x - player.getRifle().getPosition().x),2) + pow((l_position.y - player.getRifle().getPosition().y),2)) };

        const auto x_direction{ (l_position.x - player.getRifle().getPosition().x) / magnitude };
        const auto y_direction{ (l_position.y - player.getRifle().getPosition().y) / magnitude };

        if ((!player.getBullets().empty()) && (std::chrono::duration_cast<std::chrono::milliseconds>(ms - player.getBullets()[player.getBullets().size() - 1].GetSpawnTime()).count() > 300)) {
            Bullet bullet(l_position, static_cast<float>(x_direction), static_cast<float>(y_direction));
            player.setSpawnTime(bullet.GetSpawnTime());
            player.getBullets().push_back(bullet);

            // Play Shoot SFX
            Locator::GetAudio().PlaySFX(audio::SFX::RIFLE_SHOOT_NORMAL, false);
        }
        else if (std::chrono::duration_cast<std::chrono::milliseconds>(ms - player.getSpawnTime()).count() > 300) {
            Bullet bullet(l_position, static_cast<float>(x_direction), static_cast<float>(y_direction));
            player.getBullets().push_back(bullet);
            player.setSpawnTime(bullet.GetSpawnTime());

            // Play Shoot SFX
            Locator::GetAudio().PlaySFX(audio::SFX::RIFLE_SHOOT_NORMAL, false);
        }
    }
    // This loop clears the bullets list if there are any bullets that
    // have hit an enemy or out of window
    for (auto i = 0; i < player.getBullets().size(); i++) {
        const auto valid = player.getBullets()[i].Update(timestep);
        if (!valid) {
            player.getBullets().erase(player.getBullets().begin() + i);
        }
    }
}

float av::PlayerInputComponent::GetRotationAngle(Player& player) const
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
    return static_cast<float>(atan2(player.getRifle().getPosition().y - player.m_mouse_position_.y, player.getRifle().getPosition().x - player.m_mouse_position_.x) * 180.f / 3.1428 - 90);
}

sf::Vector2f av::PlayerInputComponent::GetBulletSpawn(Player& player) const
{
    const auto x{ static_cast<float>(player.getRifle().getPosition().x + player.getRifle().getSize().y * sin(
            player.getRifle().getRotation() * PI / 180)) };

    const auto y{ static_cast<float>(player.getRifle().getPosition().y - player.getRifle().getSize().y * sin(
            (90 - player.getRifle().getRotation()) * PI / 180)) };

    return { x, y };
}
