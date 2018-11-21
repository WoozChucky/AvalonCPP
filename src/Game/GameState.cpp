#include "GameState.h"
#include <AVMath.h>
#include "Tutorial.h"

using namespace av;


GameState::GameState(const sf::Vector2f l_windowSize)
:	State(l_windowSize), 
	m_CurrentLevel(new Tutorial()),
	m_NextLevel(nullptr)
{

	this->m_LevelManager.RegisterObserver(EventType::Level::RESTART, std::bind(&GameState::RestartCurrentLevel, this));
	this->m_CurrentLevel->SetLevelManager(&this->m_LevelManager);

	//Background Layer Setup
	m_Background.setFillColor(sf::Color::Blue);
	m_Background.setOutlineColor(sf::Color::Green);
	m_Background.setOutlineThickness(5.f);
	m_Background.setSize(sf::Vector2f(GetWindowSize().x * 0.35f, GetWindowSize().y * 0.45f));

	m_MinimapBackground.setFillColor(sf::Color::Red);
	m_MinimapBackground.setOutlineColor(sf::Color::Yellow);
	m_MinimapBackground.setOutlineThickness(5.f);
	m_MinimapBackground.setSize(sf::Vector2f(GetWindowSize().x * 0.35f, GetWindowSize().y * 0.45f));
	m_MinimapBackground.setPosition(AVMath::GetCenterCoordinates(GetWindowSize(), m_MinimapBackground.getGlobalBounds()));
}

void GameState::Update(const float timestep)
{
	this->m_CurrentLevel->Update(timestep);
}

void GameState::Render(sf::RenderWindow& l_window)
{
	this->m_CurrentLevel->Render(l_window);

	l_window.draw(this->m_Background);
	l_window.draw(this->m_MinimapBackground);
}

void GameState::HandleInput(sf::Event& l_event)
{
	this->m_CurrentLevel->HandleInput(l_event);

	if (l_event.type == sf::Event::LostFocus)
	{
		this->GetStateManager()->Notify(EventType::State::PAUSE);
		this->m_CurrentLevel->Pause();
	}

	if (l_event.type == sf::Event::EventType::KeyPressed)
	{
		if (l_event.key.code == sf::Keyboard::Key::Escape) {
			this->GetStateManager()->Notify(EventType::State::PAUSE);
			this->m_CurrentLevel->Pause();
		}
	}
}

void GameState::Restart()
{
	delete this->m_CurrentLevel; //NOTE: No ideia if should be doing this here. I think not. Need to research this.
	this->m_CurrentLevel = new Tutorial();
	this->m_CurrentLevel->SetLevelManager(&this->m_LevelManager);
}

void GameState::RestartCurrentLevel() const
{
	this->m_CurrentLevel->Restart();
}








