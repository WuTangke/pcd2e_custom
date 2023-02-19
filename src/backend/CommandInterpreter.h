#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <string>
#include <memory>
#include "Utilities.h"
#include "UserInterface.h"

using std::string;

namespace pdCalc {

	class CommandInterpreter
	{
		class CommandInterpreterImpl;

	public:
		explicit CommandInterpreter(UserInterface& ui);
		~CommandInterpreter();

		void commandEntered(const string& command);

	private:
		CommandInterpreter(const CommandInterpreter&) = delete;
		CommandInterpreter(CommandInterpreter&&) = delete;
		CommandInterpreter& operator=(const CommandInterpreter&) = delete;
		CommandInterpreter& operator=(CommandInterpreter&&) = delete;


		std::unique_ptr<CommandInterpreterImpl> pimpl_;
	};
}
#endif