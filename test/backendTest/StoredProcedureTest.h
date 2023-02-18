// Copyright 2016 Adam B. Singer
// Contact: PracticalDesignBook@gmail.com
//
#ifndef STORED_PROCEDURE_TEST_H
#define STORED_PROCEDURE_TEST_H

#include <QtTest/QtTest>

class StoredProcedureTest : public QObject
{
	Q_OBJECT

private slots:
	void testMissingProcedure();
	void testStoredProcedure();
};

#endif
