#pragma once

#include "Entity.h"

namespace av
{
	class InputComponent
	{
	public:
		~InputComponent() = default;
		virtual void Update(Entity& l_entity, float timestep) = 0;
	};
}