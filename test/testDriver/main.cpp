// Copyright 2016 Adam B. Singer
// Contact: PracticalDesignBook@gmail.com
//
// This file is part of pdCalc.
//
// pdCalc is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// pdCalc is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pdCalc; if not, see <http://www.gnu.org/licenses/>.

#include <QtTest/QtTest>
#include "../utilitiesTest/PublisherObserverTest.h"
#include "../backendTest/StackTest.h"

#include <iostream>
#include <QStringList>
#include <unordered_map>

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    // I use QStringList instead of argv directly because the QStringList
    // argument to qExec is constant. API doc indicates that for the argv
    // version, it may alter argv making repeated calls to qExec unstable
    // with respect to the arguments.
    QStringList args;
    for(int i = 0; i < argc; ++i)
        args.append( QString{argv[i]} );

    std::unordered_map<std::string, int> passFail;

    PublisherObserverTest pot;
    passFail["PublisherObserverTest"] = QTest::qExec(&pot, args);

    StackTest st;
    passFail["StackTest"] = QTest::qExec(&st, args);

    cout << endl;
    int errors = 0;
    for(const auto& [key, val] : passFail)
    {
        errors += val;
        if(val != 0)
            cout << "Failed test in " << key << endl;
    }

    if(errors == 0)
        cout << "All tests passed" << endl;

    return 0;
}
