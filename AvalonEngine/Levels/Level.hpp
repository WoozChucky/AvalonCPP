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

        virtual void Update(float timestep);
        virtual void HandleInput(sf::Event& l_event);
		virtual void Render(sf::RenderWindow& l_window);
		
        virtual void Pause();
        virtual void Resume();
        virtual void Restart();

        virtual void ResolveCollision(Player& l_player, Enemy& l_enemy);
        
        Subject<EventType::Level>* GetLevelManager() const;
		void SetLevelManager(Subject<EventType::Level>* l_subject);

    protected:
        sf::Vector2f GetBounds();

    private:
        sf::Vector2f m_bounds_;
    
        Subject<EventType::Level> * m_level_manager_;
    };
    
}