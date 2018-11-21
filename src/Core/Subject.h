#pragma once

#include <map>
#include <vector>
#include <functional>

#include "Locator.h"

namespace av
{
	template <typename Event>
	class Subject
	{
	public:
		Subject() = default;

		template <typename Observer>
		void RegisterObserver(const Event& l_event, Observer&& l_observer)
		{
			this->m_Observers[l_event].push_back(std::forward<Observer>(l_observer));
		}

		template <typename Observer>
		void RegisterObserver(Event&& l_event, Observer&& l_observer)
		{
			this->m_Observers[std::move(l_event)].push_back(std::forward<Observer>(l_observer));
		}

		void Notify(const Event& l_event) const
		{
			try {
				for (const auto& obs : this->m_Observers.at(l_event))
					obs(); // Notify all observers
			}
			catch (std::exception& e) {
				Locator::GetLogger() << __FUNCTION__ << "No Observers registered for Event." << e.what();
			}
		}

		//Disallow copying and assigning
		Subject(const Subject&) = delete;
		Subject& operator=(const Subject&) = delete;

	private:
		std::map<Event, std::vector<std::function<void()>>> m_Observers;
	};
}