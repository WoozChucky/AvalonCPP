#include "AnimatedSprite.h"

using namespace av;


AnimatedSprite::AnimatedSprite(sf::Time frameTime, bool paused, bool looped) :
	m_Animation(nullptr), m_FrameTime(frameTime), m_CurrentFrame(0), m_isPaused(paused), m_isLooped(looped), m_Texture(nullptr)
{

}

void AnimatedSprite::SetAnimation(const Animation& animation)
{
	m_Animation = &animation;
	m_Texture = m_Animation->GetSpriteSheet();
	m_CurrentFrame = 0;
	SetFrame(m_CurrentFrame);
}

void AnimatedSprite::SetFrameTime(sf::Time time)
{
	m_FrameTime = time;
}

void AnimatedSprite::Play()
{
	m_isPaused = false;
}

void AnimatedSprite::Play(const Animation& animation)
{
	if (GetAnimation() != &animation)
		SetAnimation(animation);
	Play();
}

void AnimatedSprite::Pause()
{
	m_isPaused = true;
}

void AnimatedSprite::Stop()
{
	m_isPaused = true;
	m_CurrentFrame = 0;
	SetFrame(m_CurrentFrame);
}

void AnimatedSprite::SetLooped(bool looped)
{
	m_isLooped = looped;
}

void AnimatedSprite::SetColor(const sf::Color& color)
{
	// Update the vertices' color
	m_Vertices[0].color = color;
	m_Vertices[1].color = color;
	m_Vertices[2].color = color;
	m_Vertices[3].color = color;
}

const Animation* AnimatedSprite::GetAnimation() const
{
	return m_Animation;
}

sf::FloatRect AnimatedSprite::GetLocalBounds() const
{
	sf::IntRect rect = m_Animation->GetFrame(m_CurrentFrame);

	float width = static_cast<float>(std::abs(rect.width));
	float height = static_cast<float>(std::abs(rect.height));

	return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect AnimatedSprite::GetGlobalBounds() const
{
	return getTransform().transformRect(GetLocalBounds());
}

bool AnimatedSprite::IsLooped() const
{
	return m_isLooped;
}

bool AnimatedSprite::IsPlaying() const
{
	return !m_isPaused;
}

sf::Time AnimatedSprite::GetFrameTime() const
{
	return m_FrameTime;
}

void AnimatedSprite::SetFrame(std::size_t newFrame, bool resetTime)
{
	if (m_Animation)
	{
		//calculate new vertex positions and texture coordiantes
		sf::IntRect rect = m_Animation->GetFrame(newFrame);

		m_Vertices[0].position = sf::Vector2f(0.f, 0.f);
		m_Vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
		m_Vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
		m_Vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

		float left = static_cast<float>(rect.left) + 0.0001f;
		float right = left + static_cast<float>(rect.width);
		float top = static_cast<float>(rect.top);
		float bottom = top + static_cast<float>(rect.height);

		m_Vertices[0].texCoords = sf::Vector2f(left, top);
		m_Vertices[1].texCoords = sf::Vector2f(left, bottom);
		m_Vertices[2].texCoords = sf::Vector2f(right, bottom);
		m_Vertices[3].texCoords = sf::Vector2f(right, top);
	}

	if (resetTime)
		m_CurrentTime = sf::Time::Zero;
}

void AnimatedSprite::Update(sf::Time deltaTime)
{
	// if not paused and we have a valid animation
	if (!m_isPaused && m_Animation)
	{
		// add delta time
		m_CurrentTime += deltaTime;

		// if current time is bigger then the frame time advance one frame
		if (m_CurrentTime >= m_FrameTime)
		{
			// reset time, but keep the remainder
			m_CurrentTime = sf::microseconds(m_CurrentTime.asMicroseconds() % m_FrameTime.asMicroseconds());

			// get next Frame index
			if (m_CurrentFrame + 1 < m_Animation->GetSize())
				m_CurrentFrame++;
			else
			{
				// animation has ended
				m_CurrentFrame = 0; // reset to start

				if (!m_isLooped)
				{
					m_isPaused = true;
				}

			}

			// set the current frame, not reseting the time
			SetFrame(m_CurrentFrame, false);
		}
	}
}

void AnimatedSprite::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_Animation && m_Texture)
	{
		states.transform *= getTransform();
		states.texture = m_Texture;
		target.draw(m_Vertices, 4, sf::Quads, states);
	}
}
