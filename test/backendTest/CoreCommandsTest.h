#ifndef CORE_COMMANDS_TEST_H
#define CORE_COMMANDS_TEST_H

#include <QtTest/QtTest>

namespace pdCalc {
	class Stack;
	class Command;
}

class CoreCommandsTest : public QObject
{
	Q_OBJECT

private slots:
	void init();
	void cleanup();

	void testEnterNumber();
	void testEnterNumberClone();
	void testSwapTopOfStackPreconditions();
	void testSwapTopOfStackClone();
	void testSwapTopOfStack();
	void testDropTopOfStackPreconditions();
	void testDropTopOfStackClone();
	void testDropTopOfStack();
	void testClearStackClone();
	void testClearStack();
	void testAddPreconditions();
	void testAddClone();
	void testAdd();
	void testSubtractPreconditions();
	void testSubtractClone();
	void testSubtract();
	void testDividePreconditions();
	void testDivideClone();
	void testDivide();
	void testSinePreconditions();
	void testSineClone();
	void testSine();
	void testCosinePreconditions();
	void testCosineClone();
	void testCosine();
	void testTangentPreconditions();
	void testTangentClone();
	void testTangent();
	void testArcsinePreconditions();
	void testArcsineClone();
	void testArcsine();
	void testArccosinePreconditions();
	void testArccosineClone();
	void testArccosine();
	void testArctangentPreconditions();
	void testArctangentClone();
	void testArctangent();
	void testPowerPreconditions();
	void testPowerClone();
	void testPower();
	void testRootPreconditions();
	void testRootClone();
	void testRoot();
	void testNegatePreconditions();
	void testNegateClone();
	void testNegate();
	void testDuplicatePreconditions();
	void testDuplicateClone();
	void testDuplicate();

private:
	pdCalc::Stack& getCheckedStack();
	void testBinaryCommandPreconditions(pdCalc::Command&);
	void testBinaryCommand(pdCalc::Command&, double top, double next, double result);
	void testUnaryCommandPreconditions(pdCalc::Command&);
	void testUnaryCommand(pdCalc::Command&, double top, double result);
	template<typename T> void testClone(pdCalc::Command& c);
	void testArcsinArccosPreconditions(pdCalc::Command* command);
};

#endif
