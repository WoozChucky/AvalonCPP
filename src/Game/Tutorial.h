#pragma once
#include "Level.h"

namespace av
{
	class Tutorial : public Level
	{
	public:
		explicit Tutorial();

		void Update(float timestep) override;
		void HandleInput(sf::Event& l_event) override;
		void Render(sf::RenderWindow& l_window) override;

		void Pause() override;
		void Resume() override;
		void Restart() override;
	};
}



