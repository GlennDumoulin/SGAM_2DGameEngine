#pragma once
#include <vector>

#include "Observer.h"

namespace sgam
{
	struct Event;

	class Subject final
	{
	public:
		Subject() = default;
		~Subject() = default;

		void Notify(const Event& event)
		{
			for (const auto& pObserver : m_pObservers)
			{
				pObserver->OnNotify(event);
			}
		}

		void AddObserver(Observer* pObserver)
		{
			if (std::find(m_pObservers.begin(), m_pObservers.end(), pObserver) == m_pObservers.end())
			{
				m_pObservers.push_back(pObserver);
			}
		}
		void RemoveObserver(const Observer* pObserver)
		{
			m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver), m_pObservers.end());
		}

	private:
		std::vector<Observer*> m_pObservers{};
	};
}
