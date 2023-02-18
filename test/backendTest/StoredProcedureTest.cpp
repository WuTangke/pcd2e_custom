#include "StoredProcedureTest.h"
#include <vector>
#include <format>
#include <string_view>

#include "Utilities.h"
#include "Stack.h"
#include "CommandDispatcher.h"
#include "UserInterface.h"

using std::vector;
using std::string;
using std::string_view;

namespace {

	class TestInterface : public pdCalc::UserInterface
	{
	public:
		TestInterface() { }
		void postMessage(string_view) override {  }
		void stackChanged() override { }
	};

}

void StoredProcedureTest::testMissingProcedure()
{
	TestInterface ui;

	try
	{
		pdCalc::StoredProcedure sp{ ui, "DoesNotExist" };
		sp.execute();
		QVERIFY(false);
	}
	catch (pdCalc::Exception& e)
	{
		QCOMPARE(e.what(), string{ "Could not open procedure" });
	}

	return;
}

void StoredProcedureTest::testStoredProcedure()
{
	pdCalc::CommandFactory::Instance().clearAllCommands();
	TestInterface ui;
	pdCalc::RegisterCoreCommands(ui);
	auto t = std::format("{}/hypotenuse", BACKEND_TEST_DIR);
	pdCalc::StoredProcedure sp(ui, t);

	pdCalc::Stack& stack = pdCalc::Stack::Instance();
	stack.push(3.0);
	stack.push(4.0);

	try
	{
		sp.execute();
		QVERIFY(true);
	}
	catch (pdCalc::Exception&)
	{
		QVERIFY(false);
	}

	vector<double> vals = stack.getElements(1);

	QCOMPARE(vals[0], 5.0);

	sp.undo();

	vals = stack.getElements(2);

	QCOMPARE(vals[0], 4.0);
	QCOMPARE(vals[1], 3.0);

	sp.execute();

	vals = stack.getElements(1);

	QCOMPARE(vals[0], 5.0);

	QVERIFY(sp.clone() == nullptr);

	return;
}
