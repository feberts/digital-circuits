#include "digitalcircuitstest.h"

#include <iostream>
#include "gateand.h"
#include "abstractinputcomponent.h"
#include "abstractoutputcomponent.h"
#include "abstractiocomponent.h"
#include "indicator.h"
#include "signalsource.h"

using namespace std;


void DigitalCircuitsTest::testAll(void)
{
    testInputsOutputs();
    testIndicator();
    testSignalSource();
    testSignalSourceIndicator();
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
        evaluate(out1->getState() == Signal::LOW);
        out1->setState(Signal::LOW);
        out1->setState(Signal::HIGH);
        evaluate(out1->getState() == Signal::HIGH);
        out1->setState(Signal::LOW);
        evaluate(out1->getState() == Signal::LOW);

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


void DigitalCircuitsTest::testIndicator(void)
{
    cout << "     ===== DigitalCircuitsTest::testIndicator =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        Indicator * ind1 = new Indicator;
        evaluate(ind1->getState() == Signal::LOW);
        Indicator * ind2 = new Indicator("ind2");
        evaluate(ind2->getState() == Signal::LOW);
        Indicator * ind3 = new Indicator(1);
        evaluate(ind3->getState() == Signal::LOW);
        Indicator * ind4 = new Indicator(2);
        evaluate(ind4->getState() == Signal::LOW);
        Indicator * ind5 = new Indicator(2, "test");
        evaluate(ind5->getState() == Signal::LOW);

        try
        {
            Indicator * ind = new Indicator(0);
            evaluate(false);
        }
        catch(invalid_argument)
        {
            evaluate(true);
        }

        try
        {
            Indicator * ind = new Indicator(0, "test");
            evaluate(false);
        }
        catch(invalid_argument)
        {
            evaluate(true);
        }

        delete ind1;
        delete ind2;
        delete ind3;
        delete ind4;
        delete ind5;
    }
}


void DigitalCircuitsTest::testSignalSource(void)
{
    cout << "     ===== DigitalCircuitsTest::testSignalSource =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        SignalSource * src1 = new SignalSource;
        evaluate(src1->getState() == Signal::OFF);
        src1->setState(Signal::ON);
        evaluate(src1->getState() == Signal::ON);
        src1->setState(Signal::OFF);
        evaluate(src1->getState() == Signal::OFF);
        delete src1;

        SignalSource * src2 = new SignalSource("src2");
        evaluate(src2->getState() == Signal::OFF);
        src2->setState(Signal::ON);
        evaluate(src2->getState() == Signal::ON);
        src2->setState(Signal::OFF);
        evaluate(src2->getState() == Signal::OFF);
        delete src2;
    }
}


void DigitalCircuitsTest::testSignalSourceIndicator(void)
{
    cout << "     ===== DigitalCircuitsTest::testSignalSourceIndicator =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        SignalSource * src1 = new SignalSource;
        SignalSource * src2 = new SignalSource;
        Indicator * ind1 = new Indicator;
        Indicator * ind2 = new Indicator(2);

        src2->setState(Signal::ON);
        evaluate(src1->getState() == Signal::OFF);
        evaluate(src2->getState() == Signal::ON);

        src1->connect(ind1, 0);
        src1->connect(ind2, 0);
        evaluate(ind1->getState() == Signal::OFF);
        evaluate(ind2->getState() == Signal::OFF);

        src2->connect(ind2, 1);
        evaluate(ind2->getState() == Signal::ON);
        evaluate(ind1->getState() == Signal::OFF);

        src1->setState(Signal::ON);
        evaluate(ind2->getState() == Signal::ON);
        evaluate(ind2->getState() == Signal::ON);

        delete src1;
        evaluate(ind2->getState() == Signal::ON);
        evaluate(ind1->getState() == Signal::OFF);

        src2->disConnect(ind2, 1);
        evaluate(ind2->getState() == Signal::OFF);

        src2->connect(ind2, 1);
        evaluate(ind2->getState() == Signal::ON);

        delete src2;
        evaluate(ind2->getState() == Signal::OFF);
    }
}


void DigitalCircuitsTest::testGateAND(void)
{
    cout << "     ===== DigitalCircuitsTest::testGateAND =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateAND * gateAnd = new GateAND("gateAnd");

        SignalSource * src0 = new SignalSource;
        SignalSource * src1 = new SignalSource;

        Indicator * ind = new Indicator;

        gateAnd->connect(ind);
        evaluate(ind->getState() == Signal::LOW);

        src0->connect(gateAnd, 0);
        src1->connect(gateAnd, 1);

        src0->setState(Signal::LOW);
        src1->setState(Signal::LOW);
        evaluate(ind->getState() == Signal::LOW);
        src0->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::LOW);
        src0->setState(Signal::LOW);
        src1->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::LOW);
        src0->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
        src1->setState(Signal::LOW);
        evaluate(ind->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd = new GateAND(3);

        SignalSource * src0 = new SignalSource;
        SignalSource * src1 = new SignalSource;
        SignalSource * src2 = new SignalSource;

        Indicator * ind = new Indicator;

        src0->connect(gateAnd, 0);
        src1->connect(gateAnd, 1);
        src2->connect(gateAnd, 2);
        gateAnd->connect(ind);

        evaluate(ind->getState() == Signal::LOW);

        src0->setState(Signal::LOW);
        src1->setState(Signal::LOW);
        src2->setState(Signal::LOW);
        evaluate(ind->getState() == Signal::LOW);
        src0->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::LOW);
        src0->setState(Signal::LOW);
        src1->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::LOW);
        src0->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::LOW);
        src0->setState(Signal::LOW);
        src1->setState(Signal::LOW);
        src2->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::LOW);
        src0->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::LOW);
        src0->setState(Signal::LOW);
        src1->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::LOW);
        src0->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
        src1->setState(Signal::LOW);
        evaluate(ind->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND(3);

        SignalSource * src1 = new SignalSource;
        SignalSource * src2 = new SignalSource;

        src1->connect(gateAnd1, 0);
        src2->connect(gateAnd1, 1);

        src1->setState(Signal::HIGH);
        src2->setState(Signal::HIGH);

        try
        {
            src1->connect(gateAnd1, 2);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        src1->connect(gateAnd2, 0);
        src2->connect(gateAnd2, 2);
        src2->setState(Signal::LOW);
        src2->setState(Signal::HIGH);

        try
        {
            src2->connect(gateAnd2, 3);
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

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src21 = new SignalSource;

        Indicator * ind2 = new Indicator;

        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src21->connect(gateAnd2, 1);

        gateAnd2->connect(ind2);

        gateAnd1->connect(gateAnd2, 0);
        evaluate(ind2->getState() == Signal::LOW);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::LOW);
        src21->setState(Signal::LOW);
        evaluate(ind2->getState() == Signal::LOW);
        src10->setState(Signal::LOW);
        src11->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::LOW);
        src10->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::LOW);
        src10->setState(Signal::LOW);
        src11->setState(Signal::LOW);
        src21->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::LOW);
        src10->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::LOW);
        src10->setState(Signal::LOW);
        src11->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::LOW);
        src10->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        src21->setState(Signal::LOW);
        evaluate(ind2->getState() == Signal::LOW);
        src21->setState(Signal::HIGH);
        src10->setState(Signal::LOW);
        evaluate(ind2->getState() == Signal::LOW);
        src10->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src21 = new SignalSource;

        Indicator * ind2 = new Indicator;

        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src21->connect(gateAnd2, 1);

        gateAnd2->connect(ind2);

        gateAnd1->connect(gateAnd2, 0);
        gateAnd1->connect(gateAnd2, 1);
        evaluate(ind2->getState() == Signal::LOW);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);
        src10->setState(Signal::LOW);
        evaluate(ind2->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src20 = new SignalSource;
        SignalSource * src21 = new SignalSource;

        Indicator * ind2 = new Indicator;

        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src20->connect(gateAnd2, 0);
        src21->connect(gateAnd2, 1);

        gateAnd2->connect(ind2);

        gateAnd1->connect(gateAnd2, 0);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        src20->setState(Signal::LOW);
        evaluate(ind2->getState() == Signal::HIGH);
    }

    {
        cout << "     ===== 4 =====" << endl;

        GateAND * gateAnd1 = new GateAND;

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);

        Indicator * ind1 = new Indicator;
        gateAnd1->connect(ind1);

        gateAnd1->connect(gateAnd1, 1);
        evaluate(ind1->getState() == Signal::LOW);

        src10->setState(Signal::HIGH);
        evaluate(ind1->getState() == Signal::LOW);
        src11->setState(Signal::HIGH);
        evaluate(ind1->getState() == Signal::HIGH);
        src11->setState(Signal::LOW);
        evaluate(ind1->getState() == Signal::HIGH);
    }

    {
        cout << "     ===== 5 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;
        GateAND * gateAnd3 = new GateAND;

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src20 = new SignalSource;
        SignalSource * src21 = new SignalSource;

        Indicator * ind3 = new Indicator;
        gateAnd3->connect(ind3);

        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src20->connect(gateAnd2, 0);
        src21->connect(gateAnd2, 1);

        gateAnd1->connect(gateAnd3, 0);
        gateAnd2->connect(gateAnd3, 1);
        evaluate(ind3->getState() == Signal::LOW);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src20->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);
        evaluate(ind3->getState() == Signal::HIGH);

        src20->setState(Signal::LOW);
        evaluate(ind3->getState() == Signal::LOW);

        gateAnd3->connect(gateAnd2, 0);
        src20->setState(Signal::HIGH);
        src20->setState(Signal::LOW);
        evaluate(ind3->getState() == Signal::HIGH);
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

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src20 = new SignalSource;
        SignalSource * src21 = new SignalSource;

        Indicator * ind3 = new Indicator;
        gateAnd3->connect(ind3);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src20->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);

        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src20->connect(gateAnd2, 0);
        src21->connect(gateAnd2, 1);

        gateAnd1->connect(gateAnd3, 0);
        evaluate(ind3->getState() == Signal::LOW);
        gateAnd2->connect(gateAnd3, 1);
        evaluate(ind3->getState() == Signal::HIGH);
    }
}


void DigitalCircuitsTest::testGateDisconnect()
{
    cout << "     ===== DigitalCircuitsTest::testGateDisconnect =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src20 = new SignalSource;
        SignalSource * src21 = new SignalSource;

        Indicator * ind1 = new Indicator;
        Indicator * ind2 = new Indicator;

        gateAnd1->connect(ind1);
        gateAnd2->connect(ind2);

        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src21->connect(gateAnd2, 1);

        gateAnd1->connect(gateAnd2, 0);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        gateAnd1->disConnect(gateAnd2, 0);
        evaluate(ind2->getState() == Signal::LOW);
        evaluate(ind1->getState() == Signal::HIGH);

        gateAnd1->connect(gateAnd2, 1);
        evaluate(ind2->getState() == Signal::LOW);
        src20->setState(Signal::HIGH);
        src20->connect(gateAnd2, 0);
        evaluate(ind2->getState() == Signal::HIGH);
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);

        Indicator * ind2 = new Indicator;
        gateAnd2->connect(ind2);

        gateAnd1->connect(gateAnd2, 0);
        gateAnd1->connect(gateAnd2, 1);
        evaluate(ind2->getState() == Signal::LOW);

        src10->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::LOW);
        src11->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        gateAnd1->disConnect(gateAnd2, 0);
        evaluate(ind2->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateAND * gateAnd1 = new GateAND;

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);

        Indicator * ind1 = new Indicator;
        gateAnd1->connect(ind1);

        gateAnd1->connect(gateAnd1, 1);
        evaluate(ind1->getState() == Signal::LOW);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        evaluate(ind1->getState() == Signal::HIGH);

        src11->setState(Signal::LOW);
        evaluate(ind1->getState() == Signal::HIGH);

        gateAnd1->disConnect(gateAnd1, 1);
        evaluate(ind1->getState() == Signal::LOW);
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

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src21 = new SignalSource;
        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src21->connect(gateAnd2, 1);

        Indicator * ind2 = new Indicator;
        gateAnd2->connect(ind2);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        delete gateAnd1;
        evaluate(ind2->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src21 = new SignalSource;
        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src21->connect(gateAnd2, 1);

        Indicator * ind2 = new Indicator;
        gateAnd2->connect(ind2);

        Indicator * ind1 = new Indicator;
        gateAnd1->connect(ind1);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        delete gateAnd2;
        evaluate(ind1->getState() == Signal::HIGH);

        src10->setState(Signal::LOW);
        evaluate(ind1->getState() == Signal::LOW);

        src11->setState(Signal::LOW);
        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        evaluate(ind1->getState() == Signal::HIGH);
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd1->connect(gateAnd2, 1);

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src21 = new SignalSource;
        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src21->connect(gateAnd2, 1);

        Indicator * ind2 = new Indicator;
        gateAnd2->connect(ind2);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        delete gateAnd1;
        evaluate(ind2->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 4 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd1->connect(gateAnd2, 1);

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src21 = new SignalSource;
        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src21->connect(gateAnd2, 1);

        Indicator * ind2 = new Indicator;
        gateAnd2->connect(ind2);

        Indicator * ind1 = new Indicator;
        gateAnd1->connect(ind1);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        delete gateAnd2;
        evaluate(ind1->getState() == Signal::HIGH);

        src10->setState(Signal::LOW);
        evaluate(ind1->getState() == Signal::LOW);

        src11->setState(Signal::LOW);
        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        evaluate(ind1->getState() == Signal::HIGH);
    }

    {
        cout << "     ===== 5 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd2->connect(gateAnd1, 1);

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src21 = new SignalSource;
        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src21->connect(gateAnd2, 1);

        Indicator * ind2 = new Indicator;
        gateAnd2->connect(ind2);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        src11->setState(Signal::LOW);
        evaluate(ind2->getState() == Signal::HIGH);

        // ----
//        src10->disConnect(gateAnd1, 0);
//        gateAnd1->disConnect(gateAnd2, 0);
//        gateAnd2->disConnect(gateAnd1, 1);
        // ----
        delete gateAnd1; // todo
        evaluate(ind2->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 6 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd2->connect(gateAnd1, 1);

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src21 = new SignalSource;
        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src21->connect(gateAnd2, 1);

        Indicator * ind2 = new Indicator;
        gateAnd2->connect(ind2);

        Indicator * ind1 = new Indicator;
        gateAnd1->connect(ind1);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        src11->setState(Signal::LOW);
        evaluate(ind2->getState() == Signal::HIGH);

        // ----
        gateAnd1->disConnect(gateAnd2, 0);
//        gateAnd2->disConnect(gateAnd1, 1);
//        src21->disConnect(gateAnd2, 1);
//        src10->disConnect(gateAnd1, 0);
        // ----
        delete gateAnd2; // todo
        evaluate(ind1->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 7 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd2->connect(gateAnd1, 1);

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src21 = new SignalSource;
        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src21->connect(gateAnd2, 1);

        Indicator * ind2 = new Indicator;
        gateAnd2->connect(ind2);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        src11->setState(Signal::LOW);
        evaluate(ind2->getState() == Signal::HIGH);

        delete src10;
        evaluate(ind2->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 8 =====" << endl;

        GateAND * gateAnd1 = new GateAND;
        GateAND * gateAnd2 = new GateAND;

        gateAnd1->connect(gateAnd2, 0);
        gateAnd2->connect(gateAnd1, 1);

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src21 = new SignalSource;
        src10->connect(gateAnd1, 0);
        src11->connect(gateAnd1, 1);
        src21->connect(gateAnd2, 1);

        Indicator * ind2 = new Indicator;
        gateAnd2->connect(ind2);

        Indicator * ind1 = new Indicator;
        gateAnd1->connect(ind1);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        src11->setState(Signal::LOW);
        evaluate(ind2->getState() == Signal::HIGH);

        delete src21;
        evaluate(ind1->getState() == Signal::LOW);
    }
}
