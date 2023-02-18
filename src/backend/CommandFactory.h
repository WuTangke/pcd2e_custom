#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include <memory>
#include <string>
#include <set>
#include <format>
#include <unordered_map>
#include <format>
#include <algorithm>
#include <ranges>
#include "Utilities.h"
#include "UserInterface.h"
#include "Command.h"
#include "CoreCommands.h"

using std::string;
using std::unordered_map;
using std::set;

namespace pdCalc {

	class CommandFactory
	{
	public:
		static CommandFactory& Instance();

		// register a new command for the factory: throws if a command with the
		// same name already exists...deregister first to replace a command
		void registerCommand(const string& name, CommandPtr c);

		// deregister a command: returns the pointer to a command and subsequently
		// removes it from the internal database of commands...returns a nullptr
		// if the command does not exist
		CommandPtr deregisterCommand(const string& name);

		// returns the number of commands currently registered
		size_t getNumberCommands() const { return factory_.size(); }

		// returns a pointer to a command without deregistering the command...returns
		// a nullptr if the command does not exist
		CommandPtr allocateCommand(const string& name) const;

		// returns true if the command is present, false otherwise
		bool hasKey(const string& s) const { return factory_.contains(s); }

		// returns a set of all the commands
		std::set<string> getAllCommandNames() const;

		// prints help for command
		string helpMessage(const string& command) const;

		// clears all commands; mainly needed for testing
		void clearAllCommands() { factory_.clear(); }

	private:
		CommandFactory() = default;
		~CommandFactory() = default;

		CommandFactory(CommandFactory&) = delete;
		CommandFactory(CommandFactory&&) = delete;
		CommandFactory& operator=(CommandFactory&) = delete;
		CommandFactory& operator=(CommandFactory&&) = delete;

	private:
		using Factory = unordered_map<string, CommandPtr>;
		Factory factory_;
	};
	void RegisterCoreCommands(UserInterface& ui);
}
#endif