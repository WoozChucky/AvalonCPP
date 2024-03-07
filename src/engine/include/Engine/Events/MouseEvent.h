#pragma once

#include <Engine/Events/Event.h>
#include <Engine/Core/Input.h>
#include <sstream>

namespace Avalon {

    class MouseMovedEvent : public Event
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

        static EventType GetStaticType() { return EventType::MouseMoved; };
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "MouseMoved"; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        F32 m_MouseX, m_MouseY;
    };

    class MouseScrolledEvent : public Event
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

        static EventType GetStaticType() { return EventType::MouseScrolled; };
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "MouseScrolled"; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        F32 m_XOffset, m_YOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        inline MouseCode GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    protected:
        MouseButtonEvent(MouseCode button)
                : m_Button(button) {}

        MouseCode m_Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(MouseCode button)
                : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        static EventType GetStaticType() { return EventType::MouseButtonPressed; };
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "MouseButtonPressed"; }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(MouseCode button)
                : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        static EventType GetStaticType() { return EventType::MouseButtonReleased; };
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "MouseButtonReleased"; }

    };

}