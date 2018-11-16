#include "circuitstest.h"

#include <iostream>
#include "gateand.h"

using namespace std;


void CircuitsTest::testAll(void)
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


bool CircuitsTest::evaluate(const bool testResult)
{
    cout << boolalpha << testResult << endl;

    if(testResult == false)
    {
        mError = true;
    }

    return testResult;
}


void CircuitsTest::testGateAND(void)
{
    cout << "     ===== CircuitsTest::testGateAND =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateAND * gateAnd = new GateAND;

        evaluate(gateAnd->getOutputState() == Signal::LOW);

        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::LOW);
        evaluate(gateAnd->getOutputState() == Signal::LOW);
        gateAnd->setInputState(0, Signal::HIGH);
        evaluate(gateAnd->getOutputState() == Signal::LOW);
        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::HIGH);
        evaluate(gateAnd->getOutputState() == Signal::LOW);
        gateAnd->setInputState(0, Signal::HIGH);
        evaluate(gateAnd->getOutputState() == Signal::HIGH);
        gateAnd->setInputState(1, Signal::LOW);
        evaluate(gateAnd->getOutputState() == Signal::LOW);
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd = new GateAND(3);

        evaluate(gateAnd->getOutputState() == Signal::LOW);

        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::LOW);
        gateAnd->setInputState(2, Signal::LOW);
        evaluate(gateAnd->getOutputState() == Signal::LOW);
        gateAnd->setInputState(0, Signal::HIGH);
        evaluate(gateAnd->getOutputState() == Signal::LOW);
        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::HIGH);
        evaluate(gateAnd->getOutputState() == Signal::LOW);
        gateAnd->setInputState(0, Signal::HIGH);
        evaluate(gateAnd->getOutputState() == Signal::LOW);
        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::LOW);
        gateAnd->setInputState(2, Signal::HIGH);
        evaluate(gateAnd->getOutputState() == Signal::LOW);
        gateAnd->setInputState(0, Signal::HIGH);
        evaluate(gateAnd->getOutputState() == Signal::LOW);
        gateAnd->setInputState(0, Signal::LOW);
        gateAnd->setInputState(1, Signal::HIGH);
        evaluate(gateAnd->getOutputState() == Signal::LOW);
        gateAnd->setInputState(0, Signal::HIGH);
        evaluate(gateAnd->getOutputState() == Signal::HIGH);
        gateAnd->setInputState(1, Signal::LOW);
        evaluate(gateAnd->getOutputState() == Signal::LOW);
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

    cout << "     ===== END of CircuitsTest::testGateAND =====" << endl;
}


void CircuitsTest::testGateConnect()
{
    cout << "     ===== CircuitsTest::testGateConnect =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::LOW);
        gateAnd2->setInputState(1, Signal::LOW);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
        gateAnd1->setInputState(0, Signal::LOW);
        gateAnd1->setInputState(1, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
        gateAnd1->setInputState(0, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
        gateAnd1->setInputState(0, Signal::LOW);
        gateAnd1->setInputState(1, Signal::LOW);
        gateAnd2->setInputState(1, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
        gateAnd1->setInputState(0, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
        gateAnd1->setInputState(0, Signal::LOW);
        gateAnd1->setInputState(1, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
        gateAnd1->setInputState(0, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);

        gateAnd2->setInputState(1, Signal::LOW);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
        gateAnd2->setInputState(1, Signal::HIGH);
        gateAnd1->setInputState(0, Signal::LOW);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
        gateAnd1->setInputState(0, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd1->connect(gateAnd2, 1);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);
        gateAnd1->setInputState(0, Signal::LOW);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);

        gateAnd2->setInputState(0, Signal::LOW);
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);
    }

    {
        cout << "     ===== 4 =====" << endl;

        GateAND * gateAnd1 = new GateAND;

        gateAnd1->connect(gateAnd1, 1);
        evaluate(gateAnd1->getOutputState() == Signal::LOW);

        gateAnd1->setInputState(0, Signal::HIGH);
        evaluate(gateAnd1->getOutputState() == Signal::LOW);
        gateAnd1->setInputState(1, Signal::HIGH);
        evaluate(gateAnd1->getOutputState() == Signal::HIGH);
        gateAnd1->setInputState(1, Signal::LOW);
        evaluate(gateAnd1->getOutputState() == Signal::HIGH);
    }

    {
        cout << "     ===== 5 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;
        GateAND * gateAnd3 = new GateAND;

        gateAnd1->connect(gateAnd3, 0);
        gateAnd2->connect(gateAnd3, 1);
        evaluate(gateAnd3->getOutputState() == Signal::LOW);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(0, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        evaluate(gateAnd3->getOutputState() == Signal::HIGH);

        gateAnd2->setInputState(0, Signal::LOW);
        evaluate(gateAnd3->getOutputState() == Signal::LOW);

        gateAnd3->connect(gateAnd2, 0);
        gateAnd2->setInputState(0, Signal::HIGH);
        gateAnd2->setInputState(0, Signal::LOW);
        evaluate(gateAnd3->getOutputState() == Signal::HIGH);
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
        evaluate(gateAnd3->getOutputState() == Signal::LOW);
        gateAnd2->connect(gateAnd3, 1);
        evaluate(gateAnd3->getOutputState() == Signal::HIGH);
    }

    cout << "     ===== END of CircuitsTest::testGateConnect =====" << endl;
}


void CircuitsTest::testGateDisconnect()
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
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);

        gateAnd1->disConnect(gateAnd2, 0);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
        evaluate(gateAnd1->getOutputState() == Signal::HIGH);

        gateAnd1->connect(gateAnd2, 1);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
        gateAnd2->setInputState(0, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd1->connect(gateAnd2, 1);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);

        gateAnd1->setInputState(0, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
        gateAnd1->setInputState(1, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);

        gateAnd1->disConnect(gateAnd2, 0);
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateAND * gateAnd1 = new GateAND;

        gateAnd1->connect(gateAnd1, 1);
        evaluate(gateAnd1->getOutputState() == Signal::LOW);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        evaluate(gateAnd1->getOutputState() == Signal::HIGH);

        gateAnd1->setInputState(1, Signal::LOW);
        evaluate(gateAnd1->getOutputState() == Signal::HIGH);

        gateAnd1->disConnect(gateAnd1, 1);
        evaluate(gateAnd1->getOutputState() == Signal::LOW);
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

    cout << "     ===== END of CircuitsTest::testGateDisconnect =====" << endl;
}


void CircuitsTest::testGateDelete()
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
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);

        delete gateAnd1;
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);

        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        gateAnd2->setInputState(1, Signal::HIGH);
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);

        delete gateAnd2;
        evaluate(gateAnd1->getOutputState() == Signal::HIGH);

        gateAnd1->setInputState(0, Signal::LOW);
        evaluate(gateAnd1->getOutputState() == Signal::LOW);

        gateAnd1->setInputState(1, Signal::LOW);
        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        evaluate(gateAnd1->getOutputState() == Signal::HIGH);
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
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);

        delete gateAnd1;
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
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
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);

        delete gateAnd2;
        evaluate(gateAnd1->getOutputState() == Signal::HIGH);

        gateAnd1->setInputState(0, Signal::LOW);
        evaluate(gateAnd1->getOutputState() == Signal::LOW);

        gateAnd1->setInputState(1, Signal::LOW);
        gateAnd1->setInputState(0, Signal::HIGH);
        gateAnd1->setInputState(1, Signal::HIGH);
        evaluate(gateAnd1->getOutputState() == Signal::HIGH);
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
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);

        gateAnd1->setInputState(1, Signal::LOW);
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);

        delete gateAnd1;
        evaluate(gateAnd2->getOutputState() == Signal::LOW);
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
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);

        gateAnd1->setInputState(1, Signal::LOW);
        evaluate(gateAnd2->getOutputState() == Signal::HIGH);

        delete gateAnd2;
        evaluate(gateAnd1->getOutputState() == Signal::LOW);
    }

    cout << "     ===== END of CircuitsTest::testGateDelete =====" << endl;
}
