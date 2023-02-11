#ifndef STACK_TEST_H
#define STACK_TEST_H

#include <QtTest/QtTest>

class StackTest : public QObject
{
	Q_OBJECT
private slots:
	void testPushPop();
	void testSwapTop();
	void testErrors();
};

#endif