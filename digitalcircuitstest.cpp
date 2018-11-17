#include "digitalcircuitstest.h"

#include <iostream>
#include "gateand.h"

using namespace std;


void DigitalCircuitsTest::testAll(void)
{
    testInputsOutputs();
    //    testGateAND();
    //    testGateConnect();
    //    testGateDisconnect();
    //    testGateDelete();

    if(mError)
    {
        cout << "\nAll tests finished: There were ERRORS\n" << endl;
    }
    else
    {
        cout << "\nAll tests finished: Everything ok\n" << endl;
    }
}


bool DigitalCircuitsTest::evaluate(const bool testResult)
{
    cout << boolalpha << testResult << endl;

    if(testResult == false)
    {
        mError = true;
    }

    return testResult;
}


void DigitalCircuitsTest::testInputsOutputs(void)
{
    cout << "     ===== DigitalCircuitsTest::testInputsOutputs =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        Output * out1 = new Output();
        out1->setState(Signal::LOW);
        out1->setState(Signal::HIGH);
        out1->setState(Signal::LOW);

        try
        {
            out1->connect(nullptr);
            evaluate(false);
        }
        catch(invalid_argument)
        {
            evaluate(true);
        }

        try
        {
            out1->disconnect(nullptr);
            evaluate(false);
        }
        catch(invalid_argument)
        {
            evaluate(true);
        }

        delete out1;
    }

    {
        cout << "     ===== 2 =====" << endl;

        try
        {
            Input * in1 = new Input(nullptr);
            evaluate(false);
        }
        catch(invalid_argument)
        {
            evaluate(true);
        }

        Input * in1 = new Input;
        evaluate(in1->getState() == Signal::LOW);
        delete in1;
    }

    {
        cout << "     ===== 3 =====" << endl;

        Output * out1 = new Output;
        Input * in1 = new Input;

        try
        {
            out1->disconnect(in1);
            evaluate(false);
        }
        catch(invalid_argument)
        {
            evaluate(true);
        }

        out1->connect(in1);

        try
        {
            out1->connect(in1);
            evaluate(false);
        }
        catch(invalid_argument)
        {
            evaluate(true);
        }

        out1->disconnect(in1);

        try
        {
            out1->disconnect(in1);
            evaluate(false);
        }
        catch(invalid_argument)
        {
            evaluate(true);
        }

        out1->connect(in1);
    }

    {
        cout << "     ===== 4 =====" << endl;

        Output * out1 = new Output;
        Input * in1 = new Input;

        out1->connect(in1);
        evaluate(in1->getState() == Signal::LOW);
        out1->setState(Signal::HIGH);
        evaluate(in1->getState() == Signal::HIGH);
        out1->setState(Signal::LOW);
        evaluate(in1->getState() == Signal::LOW);
        out1->setState(Signal::HIGH);
        evaluate(in1->getState() == Signal::HIGH);
        out1->disconnect(in1);
        evaluate(in1->getState() == Signal::LOW);
        out1->connect(in1);
        evaluate(in1->getState() == Signal::HIGH);
        delete out1;
        evaluate(in1->getState() == Signal::LOW);
        out1 = nullptr;
        evaluate(in1->getState() == Signal::LOW);
        delete in1;
    }

    {
        cout << "     ===== 4 =====" << endl;

        Output * out1 = new Output;
        Input * in1 = new Input;

        out1->setState(Signal::HIGH);
        out1->connect(in1);
        evaluate(in1->getState() == Signal::HIGH);
        delete in1;

        try
        {
            out1->disconnect(in1);
            evaluate(false);
        }
        catch(invalid_argument)
        {
            evaluate(true);
        }

        in1 = nullptr;

        try
        {
            out1->disconnect(in1);
            evaluate(false);
        }
        catch(invalid_argument)
        {
            evaluate(true);
        }

        try
        {
            out1->connect(in1);
            evaluate(false);
        }
        catch(invalid_argument)
        {
            evaluate(true);
        }

        out1->setState(Signal::LOW);
    }

    {
        cout << "     ===== 5 =====" << endl;

        Output * out1 = new Output;
        Output * out2 = new Output;
        Input * in1 = new Input;
        Input * in2 = new Input;

        out2->setState(Signal::HIGH);

        out1->connect(in1);
        out1->connect(in2);
        out2->connect(in2);

        evaluate(in1->getState() == Signal::LOW);
        evaluate(in2->getState() == Signal::HIGH);

        out1->setState(Signal::HIGH);
        evaluate(in1->getState() == Signal::HIGH);
        evaluate(in2->getState() == Signal::HIGH);

        out1->setState(Signal::LOW);
        evaluate(in1->getState() == Signal::LOW);
        evaluate(in2->getState() == Signal::HIGH);

        out1->setState(Signal::HIGH);
        out2->setState(Signal::LOW);
        evaluate(in1->getState() == Signal::HIGH);
        evaluate(in2->getState() == Signal::HIGH);

        out2->setState(Signal::HIGH);

        out1->disconnect(in2);
        evaluate(in2->getState() == Signal::HIGH);

        out1->disconnect(in1);
        evaluate(in1->getState() == Signal::LOW);
        evaluate(in2->getState() == Signal::HIGH);

        out2->connect(in1);
        evaluate(in1->getState() == Signal::HIGH);

        out2->disconnect(in1);
        out2->disconnect(in2);
        evaluate(in1->getState() == Signal::LOW);
        evaluate(in2->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 6 =====" << endl;

        Output * out1 = new Output;
        Output * out2 = new Output;
        Input * in1 = new Input;
        Input * in2 = new Input;

        out1->connect(in1);
        out1->connect(in2);
        out2->connect(in2);

        out1->setState(Signal::HIGH);
        out2->setState(Signal::HIGH);
        evaluate(in1->getState() == Signal::HIGH);
        evaluate(in2->getState() == Signal::HIGH);

        delete out1;
        evaluate(in1->getState() == Signal::LOW);
        evaluate(in2->getState() == Signal::HIGH);

        delete out2;
        evaluate(in1->getState() == Signal::LOW);
        evaluate(in2->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 7 =====" << endl;

        Output * out1 = new Output;
        Output * out2 = new Output;
        Input * in1 = new Input;
        Input * in2 = new Input;

        out1->connect(in1);
        out1->connect(in2);
        out2->connect(in2);

        out2->setState(Signal::HIGH);
        out1->setState(Signal::HIGH);

        delete in2;
        out2->setState(Signal::LOW);
        out1->setState(Signal::HIGH);

        delete in1;
        out2->setState(Signal::HIGH);
        out1->setState(Signal::LOW);

        in1 = nullptr;
        in2 = nullptr;
        out2->setState(Signal::HIGH);
        out1->setState(Signal::LOW);
    }
}


void DigitalCircuitsTest::testGateAND(void)
{
    cout << "     ===== DigitalCircuitsTest::testGateAND =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateAND * gateAnd = new GateAND("gateAnd");

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
}


void DigitalCircuitsTest::testGateConnect()
{
    cout << "     ===== DigitalCircuitsTest::testGateConnect =====" << endl;

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
}


void DigitalCircuitsTest::testGateDisconnect()
{
    cout << "     ===== DigitalCircuitsTest::testGateDisconnect =====" << endl;

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
}


void DigitalCircuitsTest::testGateDelete()
{
    cout << "     ===== DigitalCircuitsTest::testGateDelete =====" << endl;

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
}
