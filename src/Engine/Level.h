#pragma once
#include <SFML/Graphics.hpp>
#include "EventType.h"
#include "Subject.h"

namespace av
{
	class Level
	{
	public:

		explicit Level(sf::Vector2f l_bounds);
		virtual ~Level() = default;

		virtual void Update(float timestep) = 0;
		virtual void HandleInput(sf::Event& l_event) = 0;
		virtual void Render(sf::RenderWindow& l_window) = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void Restart() = 0;

		Subject<EventType::Level>* GetLevelManager() const;
		void SetLevelManager(Subject<EventType::Level>* l_subject);

	protected:
		sf::Vector2f GetBounds() const;

	private:
		sf::Vector2f m_Bounds;

		Subject<EventType::Level>* m_LevelManager;
	};
}


