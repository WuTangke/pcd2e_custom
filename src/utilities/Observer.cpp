#include "Observer.h"

namespace pdCalc {
	Observer::Observer(string_view name)
		: observerName_{ name }
	{ }

	void Observer::notify(const any& d)
	{
		notifyImpl(d);
		return;
	}
}