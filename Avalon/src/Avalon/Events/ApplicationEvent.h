#pragma once

#include "Event.h"

namespace Avalon {

	class AVALON_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(U32 width, U32 height)
			: m_Width(width), m_Height(height) {}

		inline U32 GetWidth() const { return m_Width; }
		inline U32 GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		U32 m_Width, m_Height;
	};

	class AVALON_API WindowCloseEvent : public Event
	{
		public:
			WindowCloseEvent() {}

			EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AVALON_API AppTickEvent : public Event
	{
		public:
			AppTickEvent() {}

			EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AVALON_API AppUpdateEvent : public Event
	{
		public:
			AppUpdateEvent() {}

			EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AVALON_API AppRenderEvent : public Event
	{
		public:
			AppRenderEvent() {}

			EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}