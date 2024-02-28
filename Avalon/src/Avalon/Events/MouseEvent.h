#pragma once

#include "Event.h"

namespace Avalon {

	class AVALON_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(F32 x, F32 y)
			: m_MouseX(x), m_MouseY(y) {}

		inline F32 GetX() const { return m_MouseX; }
		inline F32 GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		F32 m_MouseX, m_MouseY;
	};

	class AVALON_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(F32 xOffset, F32 yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline F32 GetXOffset() const { return m_XOffset; }
		inline F32 GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		F32 m_XOffset, m_YOffset;
	};

	class AVALON_API MouseButtonEvent : public Event
	{
	public:
		inline S32 GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(S32 button)
			: m_Button(button) {}

		S32 m_Button;
	};

	class AVALON_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(S32 button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class AVALON_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(S32 button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

	};

}