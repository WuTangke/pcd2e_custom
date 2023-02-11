#ifndef PUBLISHER_OBSERVER_TEST_H
#define PUBLISHER_OBSERVER_TEST_H

#include <QtTest/QtTest>

class ConcretePublisher;

class PublisherObserverTest : public QObject
{
	Q_OBJECT
private slots:
	void init();
	void cleanup();

	void testRegister();
	void testRegisterDuplicate();
	void testAttachObservers();
	void testRaiseEvent();
	void testDetachObservers();
	void testGetState();

private:
	ConcretePublisher* pt_;
};
#endif