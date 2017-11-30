#pragma once
#include "../Bus/Subject.hpp"
#include "../EngineUI/Events/EventType.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Enemy.hpp"

namespace av 
{
    class Level 
    {

    public:
        virtual ~Level() = default;
        explicit Level(sf::Vector2f l_bounds);

        virtual void Update(float timestep) = 0;
        virtual void HandleInput(sf::Event& l_event) = 0;
		virtual void Render(sf::RenderWindow& l_window) = 0;
		
        virtual void Pause() = 0;
        virtual void Resume() = 0;
        virtual void Restart() = 0;

        virtual void ResolveCollision(Player& l_player, Enemy& l_enemy) = 0;
        
        Subject<EventType::Level>* GetLevelManager() const;
		void SetLevelManager(Subject<EventType::Level>* l_subject);

    protected:
        sf::Vector2f GetBounds();

    private:
        sf::Vector2f m_bounds_;
    
        Subject<EventType::Level> * m_level_manager_;
    };
    
}