#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include <string_view>
#include <memory>
#include <iostream>
#include "Utilities.h"

using std::unique_ptr;
using std::string;
using std::string_view;
using std::istream;
using std::ostream;

namespace pdCalc {

	class UserInterface : protected Publisher
	{
	public:
		UserInterface() { registerEvent(CommandEntered()); }
		virtual ~UserInterface() = default;

		// post a message to the user
		virtual void postMessage(string_view m) = 0;

		// notifies the interface that the stack has changed
		virtual void stackChanged() = 0;

		using Publisher::attach;
		using Publisher::detach;

		// defines the event this publisher can raise
		// note that the string is defined in main.cpp of the application since
		// class UserInterface has no implementation file (in test driver for same
		// reason)

		// static function instead of member to avoid manual Windows dllexport requirements
		static string CommandEntered() { return "CommandIssued"; };
	};

	class Cli : public UserInterface
	{
	public:
		Cli(istream&, ostream&);
		~Cli() = default;

		// start the cli run loop
		void execute(bool suppressStartupMessage = false, bool echo = false);

	private:
		// posts a text message to the output
		void postMessage(string_view m) override;

		// updates the output when the stack is changed
		void stackChanged() override;

		void startupMessage();

		Cli(const Cli&) = delete;
		Cli(Cli&&) = delete;
		Cli& operator=(const Cli&) = delete;
		Cli& operator=(Cli&&) = delete;

		istream& in_;
		ostream& out_;
	};
}
#endif
