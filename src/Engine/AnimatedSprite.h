#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Animation.h"

namespace av
{
	class AnimatedSprite : public sf::Drawable, public sf::Transformable
	{
	public:
		explicit AnimatedSprite(sf::Time l_frameTime = sf::seconds(0.2f), bool l_paused = false, bool l_looped = true);

		void Update(sf::Time l_deltaTime);
		void SetAnimation(const Animation& l_animation);
		void SetFrameTime(sf::Time l_time);
		void Play();
		void Play(const Animation& l_animation);
		void Pause();
		void Stop();
		void SetLooped(bool l_looped);
		void SetColor(const sf::Color& l_color);
		const Animation* GetAnimation() const;
		sf::FloatRect GetLocalBounds() const;
		sf::FloatRect GetGlobalBounds() const;
		bool IsLooped() const;
		bool IsPlaying() const;
		sf::Time GetFrameTime() const;
		void SetFrame(std::size_t l_newFrame, bool l_resetTime = true);

	private:
		const Animation* m_Animation;
		sf::Time m_FrameTime;
		sf::Time m_CurrentTime;
		std::size_t m_CurrentFrame;
		bool m_isPaused;
		bool m_isLooped;
		const sf::Texture* m_Texture;
		sf::Vertex m_Vertices[4];

		virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

	};


}


