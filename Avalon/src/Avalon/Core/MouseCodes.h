#pragma once

#include "Avalon/Core/Base.h"

namespace Avalon
{
	typedef enum class MouseCode : U16
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define AV_MOUSE_BUTTON_1      ::Avalon::Mouse::Button0
#define AV_MOUSE_BUTTON_2      ::Avalon::Mouse::Button1
#define AV_MOUSE_BUTTON_2      ::Avalon::Mouse::Button2
#define AV_MOUSE_BUTTON_3      ::Avalon::Mouse::Button3
#define AV_MOUSE_BUTTON_4      ::Avalon::Mouse::Button4
#define AV_MOUSE_BUTTON_5      ::Avalon::Mouse::Button5
#define AV_MOUSE_BUTTON_6      ::Avalon::Mouse::Button6
#define AV_MOUSE_BUTTON_7      ::Avalon::Mouse::Button7
#define AV_MOUSE_BUTTON_LAST   ::Avalon::Mouse::ButtonLast
#define AV_MOUSE_BUTTON_LEFT   ::Avalon::Mouse::ButtonLeft
#define AV_MOUSE_BUTTON_RIGHT  ::Avalon::Mouse::ButtonRight
#define AV_MOUSE_BUTTON_MIDDLE ::Avalon::Mouse::ButtonMiddle