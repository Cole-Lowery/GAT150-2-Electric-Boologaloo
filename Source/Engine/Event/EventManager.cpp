#include "EnginePCH.h"
#include "Core/StringHelper.h"


#define OBSERVER_ADD(event_id)				viper::viper::EventManager::Instance().AddObserver(#event_id, *this);
#define OBSERVER_REMOVE_SELF				viper::viper::EventManager::Instance().RemoveObserver(*this)
#define EVENT_NOTIFY_DATA(event_id, data)	viper::viper::EventManager::Instance().Notify({ #event_id, data })
#define EVENT_NOTIFY(event_id)				viper::viper::EventManager::Instance().Notify({ #event_id, true })

namespace viper {
	void EventManager::AddObserver(const Event::id_t& id, IObserver* observer)
	{
		m_observers[tolower(id)].push_back(observer);
	}

	void EventManager::RemoveObserver(IObserver* observer) {
		IObserver* observerPtr = observer;

		for (auto& eventType : m_observers) {
			auto& observers = eventType.second;

			std::erase_if(observers, [observerPtr](auto& observer) 
				{ return observer == observerPtr; 
			});
		}
	}

	void EventManager::Notify(const Event& event) {
		auto iter = m_observers.find(event.id);
		if (iter != m_observers.end()) {
			for (auto observer : iter->second) {
				observer->OnNotify();
			}
		}
	}
}
