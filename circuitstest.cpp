#include "circuitstest.h"

#include <iostream>
#include "gateand.h"

using namespace std;


void CircuitsTest::testAll(void) const
{
    testGateAND();
    testGateConnect();
    testGateDisconnect();
    testGateDelete();

    if(mError)
    {
        cout << "\nAll tests finished: There were ERRORS\n" << endl;
    }
    else
    {
        cout << "\nAll tests finished: Everything ok\n" << endl;
    }
}


void CircuitsTest::evaluate(const bool testResult)
{
    if(testResult == false)
    {
        mError = true;
    }
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
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::HIGH) << endl;
        gateAnd->setInputState(1, Signal::LOW);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd = new GateAND(3);

        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;

        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::LOW);
        gateAnd->setInputState(2, Signal::LOW);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::LOW);
        gateAnd->setInputState(2, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
        gateAnd->setInputState(0, Signal::HIGH);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::HIGH) << endl;
        gateAnd->setInputState(1, Signal::LOW);
        cout << boolalpha << (gateAnd->getOutputState() == Signal::LOW) << endl;
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND(3);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);

        try
        {
            gateAnd1->setInputState(2, Signal::HIGH);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        gateAnd2->setInputState(2, Signal::HIGH);

        try
        {
            gateAnd2->setInputState(3, Signal::HIGH);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }
    }

    cout << "     ===== END =====" << endl;
}


void CircuitsTest::testGateConnect() const
{
    cout << "     ===== CircuitsTest::testGateConnect =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::LOW);
        gateAnd2->setInputState(1, Signal::LOW);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
        gateAnd1->setInputState(0, Signal::LOW);
        gateAnd1->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
        gateAnd1->setInputState(0, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
        gateAnd1->setInputState(0, Signal::LOW);
        gateAnd1->setInputState(1, Signal::LOW);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
        gateAnd1->setInputState(0, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
        gateAnd1->setInputState(0, Signal::LOW);
        gateAnd1->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
        gateAnd1->setInputState(0, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        gateAnd2->setInputState(1, Signal::LOW);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
        gateAnd2->setInputState(1, Signal::HIGH);
        gateAnd1->setInputState(0, Signal::LOW);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
        gateAnd1->setInputState(0, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd1->connect(gateAnd2, 1);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;
        gateAnd1->setInputState(0, Signal::LOW);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        gateAnd2->setInputState(0, Signal::LOW);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;
    }

    {
        cout << "     ===== 4 =====" << endl;

        GateAND * gateAnd1 = new GateAND;

        gateAnd1->connect(gateAnd1, 1);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::LOW) << endl;

        gateAnd1->setInputState(0, Signal::HIGH);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::LOW) << endl;
        gateAnd1->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::HIGH) << endl;
        gateAnd1->setInputState(1, Signal::LOW);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::HIGH) << endl;
    }

    {
        cout << "     ===== 5 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;
        GateAND * gateAnd3 = new GateAND;

        gateAnd1->connect(gateAnd3, 0);
        gateAnd2->connect(gateAnd3, 1);
        cout << boolalpha << (gateAnd3->getOutputState() == Signal::LOW) << endl;

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(0, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd3->getOutputState() == Signal::HIGH) << endl;

        gateAnd2->setInputState(0, Signal::LOW);
        cout << boolalpha << (gateAnd3->getOutputState() == Signal::LOW) << endl;

        gateAnd3->connect(gateAnd2, 0);
        gateAnd2->setInputState(0, Signal::HIGH);
        gateAnd2->setInputState(0, Signal::LOW);
        cout << boolalpha << (gateAnd3->getOutputState() == Signal::HIGH) << endl;
    }

    {
        cout << "     ===== 6 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;
        GateAND * gateAnd3 = new GateAND(3);

        gateAnd1->connect(gateAnd2, 1);
        cout << "true" << endl;

        try
        {
            gateAnd1->connect(gateAnd2, 2);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        gateAnd1->connect(gateAnd3, 2);
        cout << "true" << endl;

        try
        {
            gateAnd1->connect(gateAnd3, 3);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }
    }

    {
        cout << "     ===== 7 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;
        GateAND * gateAnd3 = new GateAND;

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(0, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);

        gateAnd1->connect(gateAnd3, 0);
        cout << boolalpha << (gateAnd3->getOutputState() == Signal::LOW) << endl;
        gateAnd2->connect(gateAnd3, 1);
        cout << boolalpha << (gateAnd3->getOutputState() == Signal::HIGH) << endl;
    }

    cout << "     ===== END =====" << endl;
}


void CircuitsTest::testGateDisconnect() const
{
    cout << "     ===== CircuitsTest::testGateDisconnect =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        gateAnd1->disConnect(gateAnd2, 0);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::HIGH) << endl;

        gateAnd1->connect(gateAnd2, 1);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
        gateAnd2->setInputState(0, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd1->connect(gateAnd2, 1);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;

        gateAnd1->setInputState(0, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
        gateAnd1->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        gateAnd1->disConnect(gateAnd2, 0);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateAND * gateAnd1 = new GateAND;

        gateAnd1->connect(gateAnd1, 1);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::LOW) << endl;

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::HIGH) << endl;

        gateAnd1->setInputState(1, Signal::LOW);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::HIGH) << endl;

        gateAnd1->disConnect(gateAnd1, 1);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::LOW) << endl;
    }

    {
        cout << "     ===== 4 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;
        GateAND * gateAnd3 = new GateAND(3);

        gateAnd1->connect(gateAnd2, 1);

        try
        {
            gateAnd1->disConnect(gateAnd2, 2);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        gateAnd1->disConnect(gateAnd2, 1);

        try
        {
            gateAnd1->disConnect(gateAnd2, 1);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        gateAnd1->connect(gateAnd3, 2);

        try
        {
            gateAnd1->disConnect(gateAnd3, 3);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        gateAnd1->disConnect(gateAnd3, 2);

        try
        {
            gateAnd1->disConnect(gateAnd3, 2);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }
    }

    cout << "     ===== END =====" << endl;
}


void CircuitsTest::testGateDelete() const
{
    cout << "     ===== CircuitsTest::testGateDelete =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        delete gateAnd1;
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        delete gateAnd2;
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::HIGH) << endl;

        gateAnd1->setInputState(0, Signal::LOW);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::LOW) << endl;

        gateAnd1->setInputState(1, Signal::LOW);
        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::HIGH) << endl;
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd1->connect(gateAnd2, 1);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        delete gateAnd1;
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
    }

    {
        cout << "     ===== 4 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd1->connect(gateAnd2, 1);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        delete gateAnd2;
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::HIGH) << endl;

        gateAnd1->setInputState(0, Signal::LOW);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::LOW) << endl;

        gateAnd1->setInputState(1, Signal::LOW);
        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::HIGH) << endl;
    }

    {
        cout << "     ===== 4 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd2->connect(gateAnd1, 1);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        gateAnd1->setInputState(1, Signal::LOW);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        delete gateAnd1;
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::LOW) << endl;
    }

    {
        cout << "     ===== 5 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd2->connect(gateAnd1, 1);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        gateAnd1->setInputState(1, Signal::LOW);
        cout << boolalpha << (gateAnd2->getOutputState() == Signal::HIGH) << endl;

        delete gateAnd2;
        cout << boolalpha << (gateAnd1->getOutputState() == Signal::LOW) << endl;
    }

    cout << "     ===== END =====" << endl;
}
