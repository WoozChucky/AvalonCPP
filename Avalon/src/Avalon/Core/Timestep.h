#pragma once

#include "Avalon/Core/Base.h"

namespace Avalon
{
	class Timestep
	{
	public:
		Timestep(F32 time = 0.0f)
			: m_Time(time)
		{
		}

		operator F32() const { return m_Time; }

		F32 GetSeconds() const { return m_Time; }
		F32 GetMilliseconds() const { return m_Time * 1000.0f; }
	
	private:
		F32 m_Time;
	};
}