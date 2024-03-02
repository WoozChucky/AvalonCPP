#pragma once

#include <Avalon.h>

struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	F32 SizeBegin, SizeEnd, SizeVariation;
	F32 LifeTime = 1.0f;
};

class ParticleSystem
{
public:
	ParticleSystem(U32 maxParticles = 10000);

	void OnUpdate(Avalon::Timestep ts);
	void OnRender(Avalon::OrthographicCamera& camera);

	void Emit(const ParticleProps& particleProps);

private:

	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec4 ColorBegin, ColorEnd;

		F32 Rotation = 0.0f;
		F32 SizeBegin, SizeEnd;
		
		F32 LifeTime = 1.0f;
		F32 LifeRemaining = 0.0f;

		bool Active = false;
	};

	std::vector<Particle> m_ParticlePool;
	U32 m_PoolIndex;
};