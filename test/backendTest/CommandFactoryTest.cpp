#include "CommandFactoryTest.h"
#include <format>
#include <set>
#include <string_view>
#include "Command.h"
#include "Utilities.h"
#include "CommandDispatcher.h"
#include "Stack.h"

using std::set;
using std::string;
using std::string_view;

namespace {

	class TestCommand : public pdCalc::Command
	{
	public:
		TestCommand(string_view optionalName = {});
		TestCommand(const TestCommand&);

		const string& getName() const { return name_; }

	private:
		void executeImpl() noexcept override { }
		void undoImpl() noexcept override { }
		TestCommand* cloneImpl() const noexcept override;
		const char* helpMessageImpl() const noexcept override { return ""; }

	private:
		string name_;
	};

	TestCommand::TestCommand(string_view n)
		: Command{}
		, name_{ n }
	{

	}

	TestCommand::TestCommand(const TestCommand& rhs)
		: Command{ rhs }
		, name_{ rhs.name_ }
	{

	}

	TestCommand* TestCommand::cloneImpl() const  noexcept
	{
		return new TestCommand{ *this };
	}

}

void CommandFactoryTest::testRegister()
{
	pdCalc::CommandFactory& cf = pdCalc::CommandFactory::Instance();
	cf.clearAllCommands();

	string name1 = "command 1";
	string name2 = "command 2";
	set<string> names = { name1, name2 };

	cf.registerCommand(name1, pdCalc::MakeCommandPtr<TestCommand>());
	cf.registerCommand(name2, pdCalc::MakeCommandPtr<TestCommand>());

	QVERIFY(cf.getNumberCommands() == 2);

	set<string> registeredCommands = cf.getAllCommandNames();

	QCOMPARE(registeredCommands, names);

	QCOMPARE(cf.hasKey(name1), true);
	QCOMPARE(cf.hasKey(name2), true);
	QCOMPARE(cf.hasKey("not present"), false);

	return;
}

void CommandFactoryTest::testDuplicateRegister()
{
	pdCalc::CommandFactory& cf = pdCalc::CommandFactory::Instance();
	cf.clearAllCommands();

	string name = "command";

	cf.registerCommand(name, pdCalc::MakeCommandPtr<TestCommand>());

	QVERIFY(cf.getNumberCommands() == 1);

	try
	{
		cf.registerCommand(name, pdCalc::MakeCommandPtr<TestCommand>());
		QVERIFY(false);
	}
	catch (pdCalc::Exception& e)
	{
		auto t = std::format("Command {} already registered", name);
		QCOMPARE(e.what(), t);
	}

	QVERIFY(cf.getNumberCommands() == 1);

	return;
}

void CommandFactoryTest::testDeregister()
{
	pdCalc::CommandFactory& cf = pdCalc::CommandFactory::Instance();
	cf.clearAllCommands();

	string name1 = "command 1";
	string name2 = "command 2";

	cf.registerCommand(name1, pdCalc::MakeCommandPtr<TestCommand>());
	cf.registerCommand(name2, pdCalc::MakeCommandPtr<TestCommand>());

	QVERIFY(cf.getNumberCommands() == 2);

	pdCalc::CommandPtr command = cf.deregisterCommand(name1);

	QVERIFY(command != nullptr);
	QVERIFY(cf.getNumberCommands() == 1);
	QCOMPARE(cf.hasKey(name1), false);
	QCOMPARE(cf.hasKey(name2), true);

	command = cf.deregisterCommand("not present");

	QVERIFY(command == nullptr);
	QVERIFY(cf.getNumberCommands() == 1);
	QCOMPARE(cf.hasKey(name1), false);
	QCOMPARE(cf.hasKey(name2), true);

	return;
}

void CommandFactoryTest::testAllocateCommand()
{
	pdCalc::CommandFactory& cf = pdCalc::CommandFactory::Instance();
	cf.clearAllCommands();

	string name = "command";

	cf.registerCommand(name, pdCalc::MakeCommandPtr<TestCommand>(name));

	QVERIFY(cf.getNumberCommands() == 1);
	QCOMPARE(cf.hasKey(name), true);

	pdCalc::CommandPtr clone = cf.allocateCommand(name);

	QVERIFY(cf.getNumberCommands() == 1);
	QCOMPARE(cf.hasKey(name), true);
	QVERIFY(clone != nullptr);
	TestCommand* testCommand = dynamic_cast<TestCommand*>(clone.get());
	QVERIFY(testCommand != nullptr);
	QCOMPARE(testCommand->getName(), name);

	clone = cf.allocateCommand("not present");

	QVERIFY(clone == nullptr);

	return;
}
