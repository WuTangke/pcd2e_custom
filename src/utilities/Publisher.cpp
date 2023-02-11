#include "Publisher.h"

namespace pdCalc {
	Publisher::Events::const_iterator Publisher::findCheckedEvent(const string& eventName) const
	{
		auto ev = events_.find(eventName);
		if (ev == events_.end())
		{
			throw Exception{ std::format("Publisher does not support event '{}'", eventName) };
		}

		return ev;
	}

	Publisher::Events::iterator Publisher::findCheckedEvent(const string& eventName)
	{
		auto ev = events_.find(eventName);
		if (ev == events_.end())
		{
			throw Exception{ std::format("Publisher does not support event '{}'", eventName) };
		}

		return ev;
	}

	void Publisher::attach(const string& eventName, unique_ptr<Observer> observer)
	{
		auto& obsList = findCheckedEvent(eventName)->second;

		if (obsList.contains(observer->name()))
			throw Exception("Observer already attached to publisher");

		obsList.insert(std::pair(observer->name(), std::move(observer)));

		return;
	}

	unique_ptr<Observer> Publisher::detach(const string& eventName, const string& observer)
	{
		auto& obsList = findCheckedEvent(eventName)->second;

		auto obs = obsList.find(observer);
		if (obs == obsList.end())
			throw Exception("Cannot detach observer because observer not found");

		auto tmp = std::move(obs->second);
		obsList.erase(obs);

		return tmp;
	}


	void Publisher::raise(const string& eventName) const
	{
		raise(eventName, any{});
	}

	void Publisher::raise(const string& eventName, const std::any d) const
	{
		const auto& obsList = findCheckedEvent(eventName)->second;
		ranges::for_each(views::values(obsList), [d](const auto& v) { v->notify(d); });

		return;
	}

	void Publisher::registerEvent(const string& eventName)
	{
		if (events_.contains(eventName))
			throw Exception{ "Event already registered" };

		events_[eventName] = ObserversList{};

		return;
	}

	void Publisher::registerEvents(const vector<string>& eventNames)
	{
		ranges::for_each(eventNames, [this](const auto& i) {registerEvent(i); });

		return;
	}

	set<string> Publisher::listEvents() const
	{
		set<string> tmp;
		ranges::for_each(events_, [&tmp](const auto& i) {tmp.insert(i.first); });

		return tmp;
	}

	set<string> Publisher::listEventObservers(const string& eventName) const
	{
		auto ev = findCheckedEvent(eventName);

		set<string> tmp;

		ranges::for_each(ev->second | views::keys, [&tmp](const auto& k) {tmp.insert(k); });

		return tmp;
	}
}