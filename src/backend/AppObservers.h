#ifndef APPOBSERVERS_H
#define APPOBSERVERS_H

#include <any>
#include <string>
#include "CommandInterpreter.h"
#include "Utilities.h"

using std::string;
using std::any;

namespace pdCalc {

	class CommandIssuedObserver : public Observer
	{
	public:
		explicit CommandIssuedObserver(CommandInterpreter& ci);

	private:
		void notifyImpl(const any&) override;

		CommandInterpreter& ci_;
	};

	class StackUpdatedObserver : public Observer
	{
	public:
		explicit StackUpdatedObserver(UserInterface& ui);

	private:
		void notifyImpl(const any&) override;

		UserInterface& ui_;
	};
}
#endif
