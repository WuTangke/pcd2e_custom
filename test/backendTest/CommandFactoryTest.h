#ifndef COMMAND_FACTORY_TEST_H
#define COMMAND_FACTORY_TEST_H

#include <QtTest/QtTest>

class CommandFactoryTest : public QObject
{
	Q_OBJECT

private slots:
	void testRegister();
	void testDuplicateRegister();
	void testDeregister();
	void testAllocateCommand();
};

#endif