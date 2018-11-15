#include "circuitstest.h"

#include <iostream>
#include "gateand.h"

using namespace std;


void CircuitsTest::testAll(void) const
{
    testGateAND();
    testGateConnections();

    cout << "\nAll tests finished\n" << endl;
}


void CircuitsTest::testGateAND(void) const
{
    cout << "     ===== CircuitsTest::testGateAND =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateAND * gateAnd = new GateAND;

        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;

        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::LOW);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::HIGH);
        gateAnd->setInputState(1, Signal::LOW);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::HIGH);
        gateAnd->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::HIGH) << endl;

        // cout << gateAnd->toString() << endl;
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd = new GateAND(3, "gateAnd");

        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;

        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::LOW);
        gateAnd->setInputState(2, Signal::LOW);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::HIGH);
        gateAnd->setInputState(1, Signal::LOW);
        gateAnd->setInputState(2, Signal::LOW);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::HIGH);
        gateAnd->setInputState(2, Signal::LOW);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::HIGH);
        gateAnd->setInputState(1, Signal::HIGH);
        gateAnd->setInputState(2, Signal::LOW);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::LOW);
        gateAnd->setInputState(2, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::HIGH);
        gateAnd->setInputState(1, Signal::LOW);
        gateAnd->setInputState(2, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::HIGH);
        gateAnd->setInputState(2, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::HIGH);
        gateAnd->setInputState(1, Signal::HIGH);
        gateAnd->setInputState(2, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::HIGH) << endl;

        // cout << gateAnd->toString() << endl;
    }
}


void CircuitsTest::testGateConnections() const
{
    cout << "     ===== CircuitsTest::testGateConnections =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateAND * gateAnd1 = new GateAND("gateAnd1");
        GateAND * gateAnd2 = new GateAND("gateAnd2");

        gateAnd1->connect(gateAnd2, 0);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        gateAnd1->setInputState(1, Signal::LOW);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;

        gateAnd1->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        gateAnd1->disConnect(gateAnd2, 0);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;

        try
        {
            gateAnd1->setInputState(1, Signal::LOW);
            gateAnd1->setInputState(0, Signal::LOW);
            gateAnd1->setInputState(0, Signal::HIGH);
            cout << "true" << endl;
        }
        catch(...)
        {
            cout << "false" << endl;
        }
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd1 = new GateAND("gateAnd1");
        GateAND * gateAnd2 = new GateAND("gateAnd2");

        gateAnd1->connect(gateAnd2, 0);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        delete gateAnd1;
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateAND * gateAnd1 = new GateAND("gateAnd1");
        GateAND * gateAnd2 = new GateAND("gateAnd2");

        gateAnd1->connect(gateAnd2, 0);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        delete gateAnd2;
        gateAnd2 = nullptr;

        gateAnd1->setInputState(1, Signal::LOW);
        cout << "true" << endl;
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::LOW) << endl;

        gateAnd1->setInputState(0, Signal::LOW);
        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::HIGH) << endl;
    }

    {
        cout << "     ===== 4 =====" << endl;

        GateAND * gateAnd1 = new GateAND("gateAnd1");
        GateAND * gateAnd2 = new GateAND("gateAnd2");
        GateAND * gateAnd3 = new GateAND(4, "gateAnd3");

        gateAnd1->connect(gateAnd2, 0);
        gateAnd1->connect(gateAnd2, 1);
        gateAnd1->connect(gateAnd3, 2);
        gateAnd1->connect(gateAnd3, 3);
        gateAnd1->connect(gateAnd1, 0);
        gateAnd1->connect(gateAnd1, 0);

        // cout << gateAnd1->toString() << endl;

        try
        {
            gateAnd2->disConnect(gateAnd3, 0);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        try
        {
            gateAnd1->disConnect(gateAnd3, 0);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        gateAnd1->disConnect(gateAnd2, 0);
        gateAnd1->disConnect(gateAnd2, 1);
        gateAnd1->disConnect(gateAnd3, 2);
        gateAnd1->disConnect(gateAnd3, 3);
        gateAnd1->disConnect(gateAnd1, 0);

        // cout << gateAnd1->toString() << endl;
    }
}
