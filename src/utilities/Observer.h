#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>
#include <any>
#include <string_view>

using std::string;
using std::any;
using std::string_view;

namespace pdCalc {

	class Observer
	{
	public:
		explicit Observer(string_view name);
		virtual ~Observer() = default;

		void notify(const any& data);

		const string& name() const { return observerName_; }

	private:
		virtual void notifyImpl(const any& data) = 0;

		string observerName_;
	};
}
#endif