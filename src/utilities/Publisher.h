#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "Observer.h"
#include "Exception.h"

#include <ranges>
#include <algorithm>
#include <any>
#include <string>
#include <format>
#include <set>
#include <memory>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::set;
using std::unique_ptr;
using std::shared_ptr;
using std::any;
using std::unordered_map;

namespace views = std::views;
namespace ranges = std::ranges;

namespace pdCalc {

	class Publisher
	{
		using ObserversList = unordered_map<string, unique_ptr<Observer>>;
		using Events = unordered_map<string, ObserversList>;

	public:
		Publisher() = default;

		void attach(const string& eventName, unique_ptr<Observer> observer);
		unique_ptr<Observer> detach(const string& eventName, const string& observerName);

		set<string> listEvents() const;
		set<string> listEventObservers(const string& eventName) const;

	protected:
		// first overload is a workaround for Visual Studio, which ICEs if data is given
		// a default parameter value of null (in a module)
		void raise(const string& eventName) const;
		void raise(const string& eventName, any data) const;

		void registerEvent(const string& eventName);
		void registerEvents(const vector<string>& eventNames);

	private:
		Events::const_iterator findCheckedEvent(const string& eventName) const;
		Events::iterator findCheckedEvent(const string& eventName);

		Events events_;
	};
}
#endif