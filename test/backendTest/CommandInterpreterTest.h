#ifndef COMMAND_DISPATCHER_TEST_H
#define COMMAND_DISPATCHER_TEST_H

#include <QtTest/QtTest>

namespace pdCalc {
	class Stack;
	class Command;
}

class CommandInterpreterTest : public QObject
{
	Q_OBJECT

private slots:
	void testCommandInterpreter();
};

#endif
