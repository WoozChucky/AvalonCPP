#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Bus/Subject.hpp"
#include "../EngineUI/Events/EventType.hpp"

namespace av
{
	class State
	{
	public:
		virtual ~State() = default;
		explicit State(const sf::Vector2f l_window_size);

		void virtual Update(float timestep) = 0;
		void virtual Render(sf::RenderWindow& l_window) = 0;
		void virtual HandleInput(sf::Event l_event) = 0;

		sf::Vector2f GetWindowSize() const;
		void SetWindowSize(const sf::Vector2f l_window_size);

		Subject<EventType::State>* GetStateManager() const;
		void SetStateManager(Subject<EventType::State>* l_subject);

	private:
		sf::Vector2f m_window_size_;
		Subject<EventType::State> * m_state_manager_;
	};
}
