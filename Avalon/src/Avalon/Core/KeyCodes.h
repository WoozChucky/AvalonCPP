#pragma once

#include "Avalon/Core/Base.h"

namespace Avalon
{
	typedef enum class KeyCode : U16
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define AV_KEY_SPACE           ::Avalon::Key::Space
#define AV_KEY_APOSTROPHE      ::Avalon::Key::Apostrophe    /* ' */
#define AV_KEY_COMMA           ::Avalon::Key::Comma         /* , */
#define AV_KEY_MINUS           ::Avalon::Key::Minus         /* - */
#define AV_KEY_PERIOD          ::Avalon::Key::Period        /* . */
#define AV_KEY_SLASH           ::Avalon::Key::Slash         /* / */
#define AV_KEY_0               ::Avalon::Key::D0
#define AV_KEY_1               ::Avalon::Key::D1
#define AV_KEY_2               ::Avalon::Key::D2
#define AV_KEY_3               ::Avalon::Key::D3
#define AV_KEY_4               ::Avalon::Key::D4
#define AV_KEY_5               ::Avalon::Key::D5
#define AV_KEY_6               ::Avalon::Key::D6
#define AV_KEY_7               ::Avalon::Key::D7
#define AV_KEY_8               ::Avalon::Key::D8
#define AV_KEY_9               ::Avalon::Key::D9
#define AV_KEY_SEMICOLON       ::Avalon::Key::Semicolon     /* ; */
#define AV_KEY_EQUAL           ::Avalon::Key::Equal         /* = */
#define AV_KEY_A               ::Avalon::Key::A
#define AV_KEY_B               ::Avalon::Key::B
#define AV_KEY_C               ::Avalon::Key::C
#define AV_KEY_D               ::Avalon::Key::D
#define AV_KEY_E               ::Avalon::Key::E
#define AV_KEY_F               ::Avalon::Key::F
#define AV_KEY_G               ::Avalon::Key::G
#define AV_KEY_H               ::Avalon::Key::H
#define AV_KEY_I               ::Avalon::Key::I
#define AV_KEY_J               ::Avalon::Key::J
#define AV_KEY_K               ::Avalon::Key::K
#define AV_KEY_L               ::Avalon::Key::L
#define AV_KEY_M               ::Avalon::Key::M
#define AV_KEY_N               ::Avalon::Key::N
#define AV_KEY_O               ::Avalon::Key::O
#define AV_KEY_P               ::Avalon::Key::P
#define AV_KEY_Q               ::Avalon::Key::Q
#define AV_KEY_R               ::Avalon::Key::R
#define AV_KEY_S               ::Avalon::Key::S
#define AV_KEY_T               ::Avalon::Key::T
#define AV_KEY_U               ::Avalon::Key::U
#define AV_KEY_V               ::Avalon::Key::V
#define AV_KEY_W               ::Avalon::Key::W
#define AV_KEY_X               ::Avalon::Key::X
#define AV_KEY_Y               ::Avalon::Key::Y
#define AV_KEY_Z               ::Avalon::Key::Z
#define AV_KEY_LEFT_BRACKET    ::Avalon::Key::LeftBracket   /* [ */
#define AV_KEY_BACKSLASH       ::Avalon::Key::Backslash     /* \ */
#define AV_KEY_RIGHT_BRACKET   ::Avalon::Key::RightBracket  /* ] */
#define AV_KEY_GRAVE_ACCENT    ::Avalon::Key::GraveAccent   /* ` */
#define AV_KEY_WORLD_1         ::Avalon::Key::World1        /* non-US #1 */
#define AV_KEY_WORLD_2         ::Avalon::Key::World2        /* non-US #2 */

/* Function keys */
#define AV_KEY_ESCAPE          ::Avalon::Key::Escape
#define AV_KEY_ENTER           ::Avalon::Key::Enter
#define AV_KEY_TAB             ::Avalon::Key::Tab
#define AV_KEY_BACKSPACE       ::Avalon::Key::Backspace
#define AV_KEY_INSERT          ::Avalon::Key::Insert
#define AV_KEY_DELETE          ::Avalon::Key::Delete
#define AV_KEY_RIGHT           ::Avalon::Key::Right
#define AV_KEY_LEFT            ::Avalon::Key::Left
#define AV_KEY_DOWN            ::Avalon::Key::Down
#define AV_KEY_UP              ::Avalon::Key::Up
#define AV_KEY_PAGE_UP         ::Avalon::Key::PageUp
#define AV_KEY_PAGE_DOWN       ::Avalon::Key::PageDown
#define AV_KEY_HOME            ::Avalon::Key::Home
#define AV_KEY_END             ::Avalon::Key::End
#define AV_KEY_CAPS_LOCK       ::Avalon::Key::CapsLock
#define AV_KEY_SCROLL_LOCK     ::Avalon::Key::ScrollLock
#define AV_KEY_NUM_LOCK        ::Avalon::Key::NumLock
#define AV_KEY_PRINT_SCREEN    ::Avalon::Key::PrintScreen
#define AV_KEY_PAUSE           ::Avalon::Key::Pause
#define AV_KEY_F1              ::Avalon::Key::F1
#define AV_KEY_F2              ::Avalon::Key::F2
#define AV_KEY_F3              ::Avalon::Key::F3
#define AV_KEY_F4              ::Avalon::Key::F4
#define AV_KEY_F5              ::Avalon::Key::F5
#define AV_KEY_F6              ::Avalon::Key::F6
#define AV_KEY_F7              ::Avalon::Key::F7
#define AV_KEY_F8              ::Avalon::Key::F8
#define AV_KEY_F9              ::Avalon::Key::F9
#define AV_KEY_F10             ::Avalon::Key::F10
#define AV_KEY_F11             ::Avalon::Key::F11
#define AV_KEY_F12             ::Avalon::Key::F12
#define AV_KEY_F13             ::Avalon::Key::F13
#define AV_KEY_F14             ::Avalon::Key::F14
#define AV_KEY_F15             ::Avalon::Key::F15
#define AV_KEY_F16             ::Avalon::Key::F16
#define AV_KEY_F17             ::Avalon::Key::F17
#define AV_KEY_F18             ::Avalon::Key::F18
#define AV_KEY_F19             ::Avalon::Key::F19
#define AV_KEY_F20             ::Avalon::Key::F20
#define AV_KEY_F21             ::Avalon::Key::F21
#define AV_KEY_F22             ::Avalon::Key::F22
#define AV_KEY_F23             ::Avalon::Key::F23
#define AV_KEY_F24             ::Avalon::Key::F24
#define AV_KEY_F25             ::Avalon::Key::F25

/* Keypad */
#define AV_KEY_KP_0            ::Avalon::Key::KP0
#define AV_KEY_KP_1            ::Avalon::Key::KP1
#define AV_KEY_KP_2            ::Avalon::Key::KP2
#define AV_KEY_KP_3            ::Avalon::Key::KP3
#define AV_KEY_KP_4            ::Avalon::Key::KP4
#define AV_KEY_KP_5            ::Avalon::Key::KP5
#define AV_KEY_KP_6            ::Avalon::Key::KP6
#define AV_KEY_KP_7            ::Avalon::Key::KP7
#define AV_KEY_KP_8            ::Avalon::Key::KP8
#define AV_KEY_KP_9            ::Avalon::Key::KP9
#define AV_KEY_KP_DECIMAL      ::Avalon::Key::KPDecimal
#define AV_KEY_KP_DIVIDE       ::Avalon::Key::KPDivide
#define AV_KEY_KP_MULTIPLY     ::Avalon::Key::KPMultiply
#define AV_KEY_KP_SUBTRACT     ::Avalon::Key::KPSubtract
#define AV_KEY_KP_ADD          ::Avalon::Key::KPAdd
#define AV_KEY_KP_ENTER        ::Avalon::Key::KPEnter
#define AV_KEY_KP_EQUAL        ::Avalon::Key::KPEqual

#define AV_KEY_LEFT_SHIFT      ::Avalon::Key::LeftShift
#define AV_KEY_LEFT_CONTROL    ::Avalon::Key::LeftControl
#define AV_KEY_LEFT_ALT        ::Avalon::Key::LeftAlt
#define AV_KEY_LEFT_SUPER      ::Avalon::Key::LeftSuper
#define AV_KEY_RIGHT_SHIFT     ::Avalon::Key::RightShift
#define AV_KEY_RIGHT_CONTROL   ::Avalon::Key::RightControl
#define AV_KEY_RIGHT_ALT       ::Avalon::Key::RightAlt
#define AV_KEY_RIGHT_SUPER     ::Avalon::Key::RightSuper
#define AV_KEY_MENU            ::Avalon::Key::Menu