#pragma once

#include <iostream>
#include <typeinfo>
#include <functional>
#include <map>
#include <vector>
#include <utility> // for std::forward

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
                this->m_observers_[l_event].push_back(std::forward<Observer>(l_observer));
            }

            template <typename Observer>
            void RegisterObserver(Event&& l_event, Observer&& l_observer)
            {
                this->m_observers_[std::move(l_event)].push_back(std::forward<Observer>(l_observer));
            }

            void Notify(const Event& l_event) const
            {
                try {
                    for(const auto& obs : this->m_observers_.at(l_event))
                        obs(); // Notify all observers
                } catch (std::exception& e) {
                    std::cout << "No Observers registered for " << typeid(l_event).name() << std::endl;
                }
            }

            //Disallow copying and assigning
            Subject(const Subject&) = delete;
            Subject& operator=(const Subject&) = delete;

        private:
            std::map<Event, std::vector<std::function<void()>>> m_observers_;
    };

}