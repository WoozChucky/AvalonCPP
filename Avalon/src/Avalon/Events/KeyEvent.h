#pragma once

#include "Event.h"

namespace Avalon {

	class AVALON_API KeyEvent : public Event
	{
	public:
		inline S32 GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(S32 keycode)
			: m_KeyCode(keycode) {}

		S32 m_KeyCode;
	};

	class AVALON_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(S32 keycode, S32 repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline S32 GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		S32 m_RepeatCount;
	};

	class AVALON_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(S32 keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class AVALON_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(S32 keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}