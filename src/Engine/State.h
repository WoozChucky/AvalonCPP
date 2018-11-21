#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <Subject.h>

#include "EventType.h"

namespace av
{
	class State
	{
	public:
		virtual ~State() = default;
		explicit State(sf::Vector2f l_window_size);

		virtual void Update(float timestep) = 0;
		virtual void Render(sf::RenderWindow& l_window) = 0;
		virtual void HandleInput(sf::Event& l_event) = 0;

		sf::Vector2f GetWindowSize() const;

		Subject<EventType::State>* GetStateManager() const;
		void SetStateManager(Subject<EventType::State>* l_subject);

	private:
		sf::Vector2f m_WindowSize;
		Subject<EventType::State> * m_StateManager;
	};
}
