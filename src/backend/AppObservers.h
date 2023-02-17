#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include <any>
#include <string>
#include "CommandInterpreter.h"
#include "Utilities.h"

using std::string;
using std::any;

namespace pdCalc {

	export class CommandIssuedObserver : public Observer
	{
	public:
		explicit CommandIssuedObserver(CommandInterpreter& ci);

	private:
		void notifyImpl(const any&) override;

		CommandInterpreter& ci_;
	};

	export class StackUpdatedObserver : public Observer
	{
	public:
		explicit StackUpdatedObserver(UserInterface& ui);

	private:
		void notifyImpl(const any&) override;

		UserInterface& ui_;
	};

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
#endif
