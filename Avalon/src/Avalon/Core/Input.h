#pragma once

#include "Avalon/Core/Base.h"
#include "Avalon/Core/KeyCodes.h"
#include "Avalon/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Avalon {

	class Input {
	public:

		static bool IsKeyPressed(KeyCode keycode);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static F32 GetMouseX();
		static F32 GetMouseY();
	};

}