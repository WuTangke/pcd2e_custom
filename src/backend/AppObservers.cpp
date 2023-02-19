#include "AppObservers.h"

namespace pdCalc {
	CommandIssuedObserver::CommandIssuedObserver(CommandInterpreter& ci)
		: Observer{ "CommandIssued" }
		, ci_{ ci }
	{ }

	void CommandIssuedObserver::notifyImpl(const any& data)
	{
		try
		{
			const auto& d = any_cast<string>(data);
			ci_.commandEntered(d);
		}
		catch (const std::bad_any_cast&)
		{
			throw Exception("Could not convert CommandIssued data to a string");
		}

		return;
	}

	StackUpdatedObserver::StackUpdatedObserver(UserInterface& ui)
		: Observer{ "StackUpdated" }
		, ui_{ ui }
	{ }

	void StackUpdatedObserver::notifyImpl(const any&)
	{
		ui_.stackChanged();

		return;
	}
}