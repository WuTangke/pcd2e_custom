#ifndef COMMAND_MANAGER_TEST_H
#define COMMAND_MANAGER_TEST_H

#include <QtTest/QtTest>

class CommandManagerTest : public QObject
{
	Q_OBJECT
private slots:
	void testExecuteStackStrategy();
	void testUndoStackStrategy();
	void testRedoStackStrategy();
	void testRedoStackFlushStackStrategy();
	void testResourceCleanupStackStrategy();
	void ignoreErrorStackStrategy();

	void testExecuteListStrategy();
	void testUndoListStrategy();
	void testRedoListStrategy();
	void testRedoStackFlushListStrategy();
	void testResourceCleanupListStrategy();
	void ignoreErrorListStrategy();

	void testExecuteListStrategyVector();
	void testUndoListStrategyVector();
	void testRedoListStrategyVector();
	void testRedoStackFlushListStrategyVector();
	void testResourceCleanupListStrategyVector();
	void ignoreErrorListStrategyVector();
};

#endif
