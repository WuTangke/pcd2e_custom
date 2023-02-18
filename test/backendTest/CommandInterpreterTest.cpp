#include "CommandInterpreterTest.h"

#include "Utilities.h"
#include "Stack.h"
#include "UserInterface.h"
#include "CommandDispatcher.h"

#include <cmath>
#include <iostream>
#include <string_view>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::string_view;

namespace {

	class TestInterface : public pdCalc::UserInterface
	{
	public:
		TestInterface() : lastMessage_{ "" } { }
		void postMessage(string_view m) override { lastMessage_ = m; }
		void stackChanged() override { }
		const string& getLastMessage() const { return lastMessage_; }

		double top() const;

	private:
		string lastMessage_;
	};

	double TestInterface::top() const
	{
		vector<double> v{ pdCalc::Stack::Instance().getElements(1) };
		return v.back();
	}

}

void CommandInterpreterTest::testCommandInterpreter()
{
	pdCalc::CommandFactory::Instance().clearAllCommands();
	pdCalc::Stack::Instance().clear();
	TestInterface ui;
	pdCalc::CommandInterpreter ci{ ui };

	ci.commandEntered("+");
	QCOMPARE(ui.getLastMessage(), string{ "Command + is not a known command" });

	pdCalc::RegisterCoreCommands(ui);

	ci.commandEntered("+");

	QCOMPARE(ui.getLastMessage(), string{ "Stack must have at least two elements" });

	ci.commandEntered("1.0");
	ci.commandEntered("2.0");

	ci.commandEntered("+");

	QCOMPARE(ui.top(), 3.0);

	ci.commandEntered("-18.3");
	ci.commandEntered("swap");
	QCOMPARE(ui.top(), 3.0);

	ci.commandEntered("drop");
	QCOMPARE(ui.top(), -18.3);

	ci.commandEntered("22");
	ci.commandEntered("undo");
	QCOMPARE(ui.top(), -18.3);

	ci.commandEntered("undo");
	QCOMPARE(ui.top(), 3.0);

	ci.commandEntered("redo");
	QCOMPARE(ui.top(), -18.3);

	ci.commandEntered("undo");
	ci.commandEntered("-");
	QCOMPARE(ui.top(), -21.3);

	ci.commandEntered("neg");
	QCOMPARE(ui.top(), 21.3);

	ci.commandEntered("7.1");
	ci.commandEntered("/");
	QCOMPARE(ui.top(), 21.3 / 7.1);

	ci.commandEntered("6");
	ci.commandEntered("2");
	ci.commandEntered("pow");
	QCOMPARE(ui.top(), 36.0);

	ci.commandEntered("27");
	ci.commandEntered("3");
	ci.commandEntered("root");
	QCOMPARE(ui.top(), 3.0);

	ci.commandEntered("*");;
	QCOMPARE(ui.top(), 108.0);

	ci.commandEntered("0.8");
	ci.commandEntered("sin");
	QCOMPARE(ui.top(), std::sin(0.8));

	ci.commandEntered("dup");
	ci.commandEntered("arcsin");
	ci.commandEntered("swap");
	double t = ui.top();
	ci.commandEntered("drop");
	QVERIFY(std::abs(ui.top() - std::asin(t)) < 1e-10);

	ci.commandEntered("0.7");
	ci.commandEntered("cos");
	QCOMPARE(ui.top(), std::cos(0.7));

	ci.commandEntered("dup");
	ci.commandEntered("arccos");
	ci.commandEntered("swap");
	t = ui.top();
	ci.commandEntered("drop");
	QVERIFY(std::abs(ui.top() - std::acos(t)) < 1e-10);

	ci.commandEntered("0.3");
	ci.commandEntered("tan");
	QCOMPARE(ui.top(), std::tan(0.3));

	ci.commandEntered("dup");
	ci.commandEntered("arctan");
	ci.commandEntered("swap");
	t = ui.top();
	ci.commandEntered("drop");
	QVERIFY(std::abs(ui.top() - std::atan(t)) < 1e-10);

	return;
}

