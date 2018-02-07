//
// Created by Nuno Levezinho on 07/02/2018.
//

#include "MenuState.h"

#define BUTTON_MARGIN 25.f

av::MenuState::MenuState(const sf::Vector2f l_window_size) :
        State(l_window_size),
        m_new_game_(sf::Vector2f(), sf::Vector2f(), sf::Color::Green),
        m_high_scores_(sf::Vector2f(), sf::Vector2f(), sf::Color::Green),
        m_quit_game_(sf::Vector2f(), sf::Vector2f(), sf::Color::Green)
{
    std::cout << GetWindowSize().x << " " << GetWindowSize().y << std::endl;
    this->InitializeUI();
}

void av::MenuState::Update(float timestep)
{

}

void av::MenuState::Render(sf::RenderWindow& l_window)
{
    l_window.draw(this->m_background_);
    this->m_new_game_.Render(l_window);
    this->m_high_scores_.Render(l_window);
    this->m_quit_game_.Render(l_window);
}

void av::MenuState::HandleInput(sf::Event& l_event)
{
    // Check if the event, was a keyboard event
    if (l_event.type == sf::Event::EventType::KeyPressed)
    {
        std::cout << "Pressed " << l_event.key.code << std::endl;

        if (l_event.key.code == sf::Keyboard::Key::Space  // Space or Enter pressed
            || l_event.key.code == sf::Keyboard::Key::Return)
        {
            switch (this->m_virtual_index_)
            {
                case 0: GetStateManager()->Notify(av::EventType::State::GAME); break;
                case 1: GetStateManager()->Notify(av::EventType::State::HIGHSCORE); break;
                case 2: GetStateManager()->Notify(av::EventType::State::EXIT); break;
                default: break;
            }
        }
        else
        {
            switch (l_event.key.code)
            {
                case sf::Keyboard::Key::Down:
                case sf::Keyboard::Key::S:
                    this->HandleArrowSelection(1);
                    break;
                case sf::Keyboard::Key::Up:
                case sf::Keyboard::Key::W:
                    this->HandleArrowSelection(-1);
                    break;
                default: /* ignored */ break;
            }
        }
    }
    else if (l_event.type == sf::Event::EventType::MouseButtonPressed)      // Mouse
    {
        const auto mouse_position = sf::Vector2f(l_event.mouseButton.x, l_event.mouseButton.y);

        if (l_event.mouseButton.button == sf::Mouse::Button::Left) // Left Click
        {
            this->HandleMouseClick(mouse_position);
        }
    }
}

void av::MenuState::HandleArrowSelection(const int l_direction)
{
    if(this->m_virtual_index_ + l_direction <= 0)
    {
        this->m_virtual_index_ = 0;
    }
    else if (this->m_virtual_index_ + l_direction >= 2)
    {
        this->m_virtual_index_ = 2;
    }
    else
    {
        this->m_virtual_index_ += l_direction;
    }

    std::cout << this->m_virtual_index_ << std::endl;
}

void av::MenuState::HandleMouseClick(const sf::Vector2f& l_mouse_position)
{
    if (m_new_game_.GetGlobalBounds().contains(l_mouse_position)) {
        std::cout << "Pressed New Game" << std::endl;
        this->GetStateManager()->Notify(av::EventType::State::GAME);
    }
    else if (m_high_scores_.GetGlobalBounds().contains(l_mouse_position)) {
        std::cout << "Pressed Highscores" << std::endl;
        this->GetStateManager()->Notify(av::EventType::State::HIGHSCORE);
    }
    else if (m_quit_game_.GetGlobalBounds().contains(l_mouse_position)) {
        std::cout << "Pressed Exit" << std::endl;
        this->GetStateManager()->Notify(av::EventType::State::EXIT);
    }
}

void av::MenuState::InitializeUI()
{
    //Background Layer Setup
    m_background_.setFillColor(sf::Color::Blue);
    m_background_.setOutlineColor(sf::Color::Green);
    m_background_.setOutlineThickness(5.f);
    m_background_.setSize(sf::Vector2f(GetWindowSize().x * 0.35f, GetWindowSize().y * 0.45f));

    const auto background_position = sf::Vector2f(
            GetWindowSize().x / 2 - m_background_.getGlobalBounds().width / 2,
            GetWindowSize().y / 2 - m_background_.getGlobalBounds().height / 2);

    m_background_.setPosition(background_position);

    //Buttons Layer Setup
    m_new_game_.SetSize(sf::Vector2f(GetWindowSize().x * 0.25f, GetWindowSize().y * 0.1f));
    m_high_scores_.SetSize(sf::Vector2f(GetWindowSize().x * 0.25f, GetWindowSize().y * 0.1f));
    m_quit_game_.SetSize(sf::Vector2f(GetWindowSize().x * 0.25f, GetWindowSize().y * 0.1f));

    const auto new_game_position = sf::Vector2f(
            GetWindowSize().x / 2 - m_new_game_.GetGlobalBounds().width / 2,
            GetWindowSize().y / 2 - m_new_game_.GetGlobalBounds().height / 2 - m_high_scores_.GetGlobalBounds().height - BUTTON_MARGIN);

    const auto high_scores_position = sf::Vector2f(
            GetWindowSize().x / 2 - m_high_scores_.GetGlobalBounds().width / 2,
            GetWindowSize().y /2 - m_high_scores_.GetGlobalBounds().height / 2);

    const auto quit_game_position = sf::Vector2f(
            GetWindowSize().x / 2 - m_quit_game_.GetGlobalBounds().width / 2,
            GetWindowSize().y / 2 - m_quit_game_.GetGlobalBounds().height / 2 + m_high_scores_.GetGlobalBounds().height + BUTTON_MARGIN);


    m_new_game_.SetPosition(new_game_position);
    m_new_game_.SetText("New Game");

    m_high_scores_.SetText("Highscores");
    m_high_scores_.SetPosition(high_scores_position);

    m_quit_game_.SetText("Exit");
    m_quit_game_.SetPosition(quit_game_position);
}