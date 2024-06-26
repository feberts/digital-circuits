#include "digitalcircuitstest.h"

#include <iostream>
#include "../gates/gateand.h"
#include "../gates/gateor.h"
#include "../gates/gatexor.h"
#include "../devices/indicator.h"
#include "../devices/signalsource.h"
#include "../gates/gatenand.h"
#include "../gates/gatenot.h"
#include "../devices/switch.h"
#include "../devices/pushbutton.h"

using namespace std;


void DigitalCircuitsTest::testAll(void)
{
    testInputsOutputs();
    testIndicator();
    testSignalSource();
    testSignalSourceIndicator();
    testGateAND();
    testGateOR();
    testGateXOR();
    testGateNAND();
    testGateNOT();
    testGateConnect();
    testGateDisconnect();
    testGateDelete();
    testFullAdder();
    testSwitch();
    testPushButton();
    testNBitFullAdder();
#ifndef EVALUATE_IMMEDIATELY
    testUnstableCircuits();
#endif
    //    testManualTests();

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

        evaluate(true);
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

        src2->disconnect(ind2, 1);
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

        evaluate(gateAnd->getState() == Signal::LOW);

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

        evaluate(gateAnd->getState() == Signal::LOW);

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


void DigitalCircuitsTest::testGateOR(void)
{
    cout << "     ===== DigitalCircuitsTest::testGateOR =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateOR * gateOr = new GateOR("gateOr");

        SignalSource * src0 = new SignalSource;
        SignalSource * src1 = new SignalSource;

        Indicator * ind = new Indicator;

        evaluate(gateOr->getState() == Signal::LOW);

        gateOr->connect(ind);
        evaluate(ind->getState() == Signal::LOW);

        src0->connect(gateOr, 0);
        src1->connect(gateOr, 1);

        src0->setState(Signal::LOW);
        src1->setState(Signal::LOW);
        evaluate(ind->getState() == Signal::LOW);
        src0->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
        src0->setState(Signal::LOW);
        src1->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
        src0->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
        src1->setState(Signal::LOW);
        evaluate(ind->getState() == Signal::HIGH);
        src0->setState(Signal::LOW);
        evaluate(ind->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateOR * gateOr = new GateOR(3);

        SignalSource * src0 = new SignalSource;
        SignalSource * src1 = new SignalSource;
        SignalSource * src2 = new SignalSource;

        Indicator * ind = new Indicator;

        evaluate(gateOr->getState() == Signal::LOW);

        src0->connect(gateOr, 0);
        src1->connect(gateOr, 1);
        src2->connect(gateOr, 2);
        gateOr->connect(ind);

        evaluate(ind->getState() == Signal::LOW);

        src0->setState(Signal::LOW);
        src1->setState(Signal::LOW);
        src2->setState(Signal::LOW);
        evaluate(ind->getState() == Signal::LOW);
        src0->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
        src0->setState(Signal::LOW);
        src1->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
        src0->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
        src0->setState(Signal::LOW);
        src1->setState(Signal::LOW);
        src2->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
        src0->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
        src0->setState(Signal::LOW);
        src1->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
        src0->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
        src1->setState(Signal::LOW);
        evaluate(ind->getState() == Signal::HIGH);
        src0->setState(Signal::LOW);
        evaluate(ind->getState() == Signal::HIGH);
        src2->setState(Signal::LOW);
        evaluate(ind->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateOR * gateOr1 = new GateOR;
        GateOR * gateOr2 = new GateOR(3);

        SignalSource * src1 = new SignalSource;
        SignalSource * src2 = new SignalSource;

        src1->connect(gateOr1, 0);
        src2->connect(gateOr1, 1);

        src1->setState(Signal::HIGH);
        src2->setState(Signal::HIGH);

        try
        {
            src1->connect(gateOr1, 2);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        src1->connect(gateOr2, 0);
        src2->connect(gateOr2, 2);
        src2->setState(Signal::LOW);
        src2->setState(Signal::HIGH);

        try
        {
            src2->connect(gateOr2, 3);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }
    }

    {
        cout << "     ===== 4 =====" << endl;

        // manual call of evaluate()

        GateOR * gateOr = new GateOR("gateOr");

        SignalSource * src0 = new SignalSource;
        SignalSource * src1 = new SignalSource;

        Indicator * ind = new Indicator;

        gateOr->connect(ind);
        src0->connect(gateOr, 0);
        src1->connect(gateOr, 1);

        gateOr->evaluate();
        ind->evaluate();
        evaluate(ind->getState() == Signal::LOW);

        src0->setState(Signal::HIGH);
        gateOr->evaluate();
        ind->evaluate();
        evaluate(ind->getState() == Signal::HIGH);

        src0->setState(Signal::LOW);
        gateOr->evaluate();
        ind->evaluate();
        evaluate(ind->getState() == Signal::LOW);

        src1->setState(Signal::HIGH);
        gateOr->evaluate();
        ind->evaluate();
        evaluate(ind->getState() == Signal::HIGH);
    }
}


void DigitalCircuitsTest::testGateXOR(void) // template
{
    cout << "     ===== DigitalCircuitsTest::testGateXOR =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateXOR * gateXOR = new GateXOR("gateAnd");

        SignalSource * src0 = new SignalSource;
        SignalSource * src1 = new SignalSource;

        evaluate(gateXOR->getState() == Signal::LOW);

        src0->connect(gateXOR, 0);
        src1->connect(gateXOR, 1);

        evaluate(gateXOR->getState() == Signal::LOW);

        src0->setState(Signal::LOW);
        src1->setState(Signal::LOW);
        evaluate(gateXOR->getState() == Signal::LOW); // 0
        src0->setState(Signal::HIGH);
        src1->setState(Signal::LOW);
        evaluate(gateXOR->getState() == Signal::HIGH); // 1
        src0->setState(Signal::LOW);
        src1->setState(Signal::HIGH);
        evaluate(gateXOR->getState() == Signal::HIGH); // 2
        src0->setState(Signal::HIGH);
        src1->setState(Signal::HIGH);
        evaluate(gateXOR->getState() == Signal::LOW); // 3

        src1->setState(Signal::LOW);
        evaluate(gateXOR->getState() == Signal::HIGH);
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateXOR * gateAnd = new GateXOR(3);

        SignalSource * src0 = new SignalSource;
        SignalSource * src1 = new SignalSource;
        SignalSource * src2 = new SignalSource;

        evaluate(gateAnd->getState() == Signal::LOW);

        src0->connect(gateAnd, 0);
        src1->connect(gateAnd, 1);
        src2->connect(gateAnd, 2);

        evaluate(gateAnd->getState() == Signal::LOW);

        src0->setState(Signal::LOW);
        src1->setState(Signal::LOW);
        src2->setState(Signal::LOW);
        evaluate(gateAnd->getState() == Signal::LOW); // 0
        src0->setState(Signal::HIGH);
        src1->setState(Signal::LOW);
        src2->setState(Signal::LOW);
        evaluate(gateAnd->getState() == Signal::HIGH); // 1
        src0->setState(Signal::LOW);
        src1->setState(Signal::HIGH);
        src2->setState(Signal::LOW);
        evaluate(gateAnd->getState() == Signal::HIGH); // 2
        src0->setState(Signal::HIGH);
        src1->setState(Signal::HIGH);
        src2->setState(Signal::LOW);
        evaluate(gateAnd->getState() == Signal::LOW); // 3
        src0->setState(Signal::LOW);
        src1->setState(Signal::LOW);
        src2->setState(Signal::HIGH);
        evaluate(gateAnd->getState() == Signal::HIGH); // 4
        src0->setState(Signal::HIGH);
        src1->setState(Signal::LOW);
        src2->setState(Signal::HIGH);
        evaluate(gateAnd->getState() == Signal::LOW); // 5
        src0->setState(Signal::LOW);
        src1->setState(Signal::HIGH);
        src2->setState(Signal::HIGH);
        evaluate(gateAnd->getState() == Signal::LOW); // 6
        src0->setState(Signal::HIGH);
        src1->setState(Signal::HIGH);
        src2->setState(Signal::HIGH);
        evaluate(gateAnd->getState() == Signal::LOW); // 7

        src2->setState(Signal::LOW);
        evaluate(gateAnd->getState() == Signal::LOW);
        src1->setState(Signal::LOW);
        evaluate(gateAnd->getState() == Signal::HIGH);
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateXOR * gateXOR1 = new GateXOR;
        GateXOR * gateXOR2 = new GateXOR(3);

        SignalSource * src1 = new SignalSource;
        SignalSource * src2 = new SignalSource;

        src1->connect(gateXOR1, 0);
        src2->connect(gateXOR1, 1);

        src1->setState(Signal::HIGH);
        src2->setState(Signal::HIGH);

        try
        {
            src1->connect(gateXOR1, 2);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        src1->connect(gateXOR2, 0);
        src2->connect(gateXOR2, 2);
        src2->setState(Signal::LOW);
        src2->setState(Signal::HIGH);

        try
        {
            src2->connect(gateXOR2, 3);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }
    }
}


void DigitalCircuitsTest::testGateNAND(void)
{
    cout << "     ===== DigitalCircuitsTest::testGateNAND =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateNAND * gateNAND = new GateNAND("gateNAND");

        SignalSource * src0 = new SignalSource;
        SignalSource * src1 = new SignalSource;

        evaluate(gateNAND->getState() == Signal::HIGH);

        src0->connect(gateNAND, 0);
        src1->connect(gateNAND, 1);

        evaluate(gateNAND->getState() == Signal::HIGH);

        src0->setState(Signal::LOW);
        src1->setState(Signal::LOW);
        evaluate(gateNAND->getState() == Signal::HIGH); // 0
        src0->setState(Signal::HIGH);
        src1->setState(Signal::LOW);
        evaluate(gateNAND->getState() == Signal::HIGH); // 1
        src0->setState(Signal::LOW);
        src1->setState(Signal::HIGH);
        evaluate(gateNAND->getState() == Signal::HIGH); // 2
        src0->setState(Signal::HIGH);
        src1->setState(Signal::HIGH);
        evaluate(gateNAND->getState() == Signal::LOW); // 3

        src1->setState(Signal::LOW);
        evaluate(gateNAND->getState() == Signal::HIGH);
    }

    {
        cout << "     ===== 2 =====" << endl;

        GateNAND * gateNAND = new GateNAND(3);

        SignalSource * src0 = new SignalSource;
        SignalSource * src1 = new SignalSource;
        SignalSource * src2 = new SignalSource;

        evaluate(gateNAND->getState() == Signal::HIGH);

        src0->connect(gateNAND, 0);
        src1->connect(gateNAND, 1);
        src2->connect(gateNAND, 2);

        evaluate(gateNAND->getState() == Signal::HIGH);

        src0->setState(Signal::LOW);
        src1->setState(Signal::LOW);
        src2->setState(Signal::LOW);
        evaluate(gateNAND->getState() == Signal::HIGH); // 0
        src0->setState(Signal::HIGH);
        src1->setState(Signal::LOW);
        src2->setState(Signal::LOW);
        evaluate(gateNAND->getState() == Signal::HIGH); // 1
        src0->setState(Signal::LOW);
        src1->setState(Signal::HIGH);
        src2->setState(Signal::LOW);
        evaluate(gateNAND->getState() == Signal::HIGH); // 2
        src0->setState(Signal::HIGH);
        src1->setState(Signal::HIGH);
        src2->setState(Signal::LOW);
        evaluate(gateNAND->getState() == Signal::HIGH); // 3
        src0->setState(Signal::LOW);
        src1->setState(Signal::LOW);
        src2->setState(Signal::HIGH);
        evaluate(gateNAND->getState() == Signal::HIGH); // 4
        src0->setState(Signal::HIGH);
        src1->setState(Signal::LOW);
        src2->setState(Signal::HIGH);
        evaluate(gateNAND->getState() == Signal::HIGH); // 5
        src0->setState(Signal::LOW);
        src1->setState(Signal::HIGH);
        src2->setState(Signal::HIGH);
        evaluate(gateNAND->getState() == Signal::HIGH); // 6
        src0->setState(Signal::HIGH);
        src1->setState(Signal::HIGH);
        src2->setState(Signal::HIGH);
        evaluate(gateNAND->getState() == Signal::LOW); // 7

        src2->setState(Signal::LOW);
        evaluate(gateNAND->getState() == Signal::HIGH);
        src1->setState(Signal::LOW);
        evaluate(gateNAND->getState() == Signal::HIGH);
    }

    {
        cout << "     ===== 3 =====" << endl;

        GateNAND * gateNAND1 = new GateNAND;
        GateNAND * gateNAND2 = new GateNAND(3);

        SignalSource * src1 = new SignalSource;
        SignalSource * src2 = new SignalSource;

        src1->connect(gateNAND1, 0);
        src2->connect(gateNAND1, 1);

        src1->setState(Signal::HIGH);
        src2->setState(Signal::HIGH);

        try
        {
            src1->connect(gateNAND1, 2);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        src1->connect(gateNAND2, 0);
        src2->connect(gateNAND2, 2);
        src2->setState(Signal::LOW);
        src2->setState(Signal::HIGH);

        try
        {
            src2->connect(gateNAND2, 3);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }
    }
}


void DigitalCircuitsTest::testGateNOT(void)
{
    cout << "     ===== DigitalCircuitsTest::testGateNOT =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        GateNOT * gateNOT = new GateNOT;

        evaluate(gateNOT->getState() == Signal::HIGH);

        SignalSource * src = new SignalSource;
        src->connect(gateNOT);
        evaluate(gateNOT->getState() == Signal::HIGH);
        src->setState(Signal::HIGH);
        evaluate(gateNOT->getState() == Signal::LOW);
        src->disconnect(gateNOT);
        evaluate(gateNOT->getState() == Signal::HIGH);
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

        gateAnd1->disconnect(gateAnd2, 0);
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

        gateAnd1->disconnect(gateAnd2, 0);
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

        gateAnd1->disconnect(gateAnd1, 1);
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
            gateAnd1->disconnect(gateAnd2, 2);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        gateAnd1->disconnect(gateAnd2, 1);

        try
        {
            gateAnd1->disconnect(gateAnd2, 1);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        gateAnd1->connect(gateAnd3, 2);

        try
        {
            gateAnd1->disconnect(gateAnd3, 3);
            cout << "false" << endl;
        }
        catch(invalid_argument)
        {
            cout << "true" << endl;
        }

        gateAnd1->disconnect(gateAnd3, 2);

        try
        {
            gateAnd1->disconnect(gateAnd3, 2);
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

        delete gateAnd1;
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

        delete gateAnd2;
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

    {
        cout << "     ===== 9 =====" << endl;

        GateOR * gateOr1 = new GateOR;
        GateOR * gateOr2 = new GateOR;

        gateOr1->connect(gateOr2, 0);
        gateOr2->connect(gateOr1, 1);

        SignalSource * src10 = new SignalSource;
        SignalSource * src11 = new SignalSource;
        SignalSource * src21 = new SignalSource;
        src10->connect(gateOr1, 0);
        src11->connect(gateOr1, 1);
        src21->connect(gateOr2, 1);

        Indicator * ind2 = new Indicator;
        gateOr2->connect(ind2);

        Indicator * ind1 = new Indicator;
        gateOr1->connect(ind1);

        src10->setState(Signal::HIGH);
        src11->setState(Signal::HIGH);
        src21->setState(Signal::HIGH);
        evaluate(ind2->getState() == Signal::HIGH);

        src11->setState(Signal::LOW);
        evaluate(ind2->getState() == Signal::HIGH);

        src10->setState(Signal::LOW);
        delete gateOr2;
        evaluate(ind1->getState() == Signal::LOW);
    }
}


void DigitalCircuitsTest::testFullAdder(void)
{
    cout << "     ===== DigitalCircuitsTest::testFullAdder =====" << endl;

    {
        GateAND * and1 = new GateAND;
        GateAND * and2 = new GateAND;
        GateXOR * xor1 = new GateXOR;
        GateXOR * xor2 = new GateXOR;
        GateOR * or1 = new GateOR;

        SignalSource * A = new SignalSource;
        SignalSource * B = new SignalSource;
        SignalSource * Cin = new SignalSource;

        Indicator * S = new Indicator;
        Indicator * Cout = new Indicator;

        A->connect(xor1, 1);
        A->connect(and2, 1);
        B->connect(xor1, 0);
        B->connect(and2, 0);
        Cin->connect(xor2, 0);
        Cin->connect(and1, 0);
        xor1->connect(xor2, 1);
        xor1->connect(and1, 1);
        xor2->connect(S);
        and1->connect(or1, 1);
        and2->connect(or1, 0);
        or1->connect(Cout);

        // 0
        A->setState(Signal::LOW);
        B->setState(Signal::LOW);
        Cin->setState(Signal::LOW);
        evaluate(Cout->getState() == Signal::LOW);
        evaluate(S->getState() == Signal::LOW);

        // 1
        A->setState(Signal::LOW);
        B->setState(Signal::LOW);
        Cin->setState(Signal::HIGH);
        evaluate(Cout->getState() == Signal::LOW);
        evaluate(S->getState() == Signal::HIGH);

        // 2
        A->setState(Signal::LOW);
        B->setState(Signal::HIGH);
        Cin->setState(Signal::LOW);
        evaluate(Cout->getState() == Signal::LOW);
        evaluate(S->getState() == Signal::HIGH);

        // 3
        A->setState(Signal::LOW);
        B->setState(Signal::HIGH);
        Cin->setState(Signal::HIGH);
        evaluate(Cout->getState() == Signal::HIGH);
        evaluate(S->getState() == Signal::LOW);

        // 4
        A->setState(Signal::HIGH);
        B->setState(Signal::LOW);
        Cin->setState(Signal::LOW);
        evaluate(Cout->getState() == Signal::LOW);
        evaluate(S->getState() == Signal::HIGH);

        // 5
        A->setState(Signal::HIGH);
        B->setState(Signal::LOW);
        Cin->setState(Signal::HIGH);
        evaluate(Cout->getState() == Signal::HIGH);
        evaluate(S->getState() == Signal::LOW);

        // 6
        A->setState(Signal::HIGH);
        B->setState(Signal::HIGH);
        Cin->setState(Signal::LOW);
        evaluate(Cout->getState() == Signal::HIGH);
        evaluate(S->getState() == Signal::LOW);

        // 7
        A->setState(Signal::HIGH);
        B->setState(Signal::HIGH);
        Cin->setState(Signal::HIGH);
        evaluate(Cout->getState() == Signal::HIGH);
        evaluate(S->getState() == Signal::HIGH);

        B->setState(Signal::LOW);
        Cin->setState(Signal::LOW);
        evaluate(Cout->getState() == Signal::LOW);
        evaluate(S->getState() == Signal::HIGH);
    }
}


void DigitalCircuitsTest::testSwitch(void)
{
    cout << "     ===== DigitalCircuitsTest::testSwitch =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        SignalSource * src = new SignalSource;
        Switch * sw = new Switch;
        Indicator * ind = new Indicator;

        evaluate(sw->getState() == Signal::LOW);

        sw->toogle(Signal::ON);
        evaluate(sw->getState() == Signal::LOW);

        sw->toogle(Signal::OFF);
        src->connect(sw);
        sw->connect(ind);
        evaluate(ind->getState() == Signal::LOW);

        src->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::LOW);
        evaluate(sw->getState() == Signal::LOW);

        sw->toogle(Signal::ON);
        evaluate(ind->getState() == Signal::HIGH);
        evaluate(sw->getState() == Signal::HIGH);

        sw->toogle(Signal::OFF);
        evaluate(ind->getState() == Signal::LOW);
        evaluate(sw->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 2 =====" << endl;

        SignalSource * src = new SignalSource;
        Switch * sw = new Switch;
        Indicator * ind = new Indicator;

        sw->toogle(Signal::ON);
        src->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::LOW);

        src->connect(sw);
        sw->connect(ind);
        evaluate(ind->getState() == Signal::HIGH);
    }

    {
        cout << "     ===== 3 =====" << endl;

        SignalSource * src = new SignalSource;
        Switch * sw = new Switch;
        Indicator * ind = new Indicator;

        sw->toogle(Signal::ON);
        src->setState(Signal::LOW);
        evaluate(ind->getState() == Signal::LOW);

        src->connect(sw);
        sw->connect(ind);
        evaluate(ind->getState() == Signal::LOW);

        src->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::HIGH);
    }

    {
        cout << "     ===== 4 =====" << endl;

        SignalSource * src = new SignalSource;
        Switch * sw = new Switch;
        Indicator * ind = new Indicator;

        sw->toogle(Signal::OFF);
        src->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::LOW);

        src->connect(sw);
        sw->connect(ind);
        evaluate(ind->getState() == Signal::LOW);

        sw->toogle(Signal::ON);
        evaluate(ind->getState() == Signal::HIGH);
    }
}


void DigitalCircuitsTest::testPushButton(void)
{
    cout << "     ===== DigitalCircuitsTest::testPushButton =====" << endl;

    {
        cout << "     ===== 1 =====" << endl;

        SignalSource * src = new SignalSource;
        PushButton * pb = new PushButton;
        Indicator * indAnd = new Indicator;
        Indicator * indPb = new Indicator;
        GateAND * gateAnd = new GateAND;

        src->connect(gateAnd, 0);
        src->connect(pb);
        pb->connect(gateAnd, 1);
        gateAnd->connect(gateAnd, 1);
        gateAnd->connect(indAnd);
        pb->connect(indPb);

        src->setState(Signal::HIGH);

        evaluate(indAnd->getState() == Signal::LOW);
        evaluate(indPb->getState() == Signal::LOW);

        pb->push();

        evaluate(indAnd->getState() == Signal::HIGH);
        evaluate(indPb->getState() == Signal::LOW);
    }

    {
        cout << "     ===== 2 =====" << endl;

        // latching

        SignalSource * src = new SignalSource;
        PushButton * pbOn = new PushButton;
        PushButton * pbOff = new PushButton;
        Indicator * indAnd = new Indicator;
        Indicator * indPb = new Indicator;
        GateAND * gateAnd = new GateAND;
        GateXOR * gateXor = new GateXOR;

        src->connect(gateXor, 1);
        src->connect(pbOn);
        src->connect(pbOff);
        pbOn->connect(gateAnd, 1);
        gateAnd->connect(gateAnd, 1);
        gateAnd->connect(indAnd);
        gateXor->connect(gateAnd, 0);
        pbOn->connect(indPb);
        pbOff->connect(indPb);
        pbOff->connect(gateXor, 0);

        src->setState(Signal::HIGH);

        evaluate(indAnd->getState() == Signal::LOW);
        evaluate(indPb->getState() == Signal::LOW);

        pbOn->push();

        evaluate(indAnd->getState() == Signal::HIGH);
        evaluate(indPb->getState() == Signal::LOW);

        pbOff->push();

        evaluate(indAnd->getState() == Signal::LOW);
        evaluate(indPb->getState() == Signal::LOW);
    }
}


void DigitalCircuitsTest::testNBitFullAdder(void)
{
    cout << "     ===== DigitalCircuitsTest::testNBitFullAdder =====" << endl;

    {
        vector<SignalSource *> registerA;
        vector<SignalSource *> registerB;
        vector<Indicator *> registerS;

        SignalSource * A = new SignalSource;
        SignalSource * B = new SignalSource;
        Indicator * S = new Indicator;

        GateAND * and1 = new GateAND;
        GateAND * and2 = new GateAND;
        GateXOR * xor1 = new GateXOR;
        GateXOR * xor2 = new GateXOR;
        GateOR * or1 = new GateOR;
        GateOR * or1_old = or1;

        registerA.push_back(A);
        registerB.push_back(B);
        registerS.push_back(S);

        A->connect(xor1, 1);
        A->connect(and2, 1);
        B->connect(xor1, 0);
        B->connect(and2, 0);
        xor1->connect(xor2, 1);
        xor1->connect(and1, 1);
        xor2->connect(S);
        and1->connect(or1, 1);
        and2->connect(or1, 0);

        for(unsigned int nbit = 1; nbit < 3; nbit++)
        {
            and1 = new GateAND;
            and2 = new GateAND;
            xor1 = new GateXOR;
            xor2 = new GateXOR;
            or1 = new GateOR;

            A = new SignalSource;
            B = new SignalSource;
            S = new Indicator;

            registerA.push_back(A);
            registerB.push_back(B);
            registerS.push_back(S);

            A->connect(xor1, 1);
            A->connect(and2, 1);
            B->connect(xor1, 0);
            B->connect(and2, 0);
            or1_old->connect(xor2, 0);
            or1_old->connect(and1, 0);
            xor1->connect(xor2, 1);
            xor1->connect(and1, 1);
            xor2->connect(S);
            and1->connect(or1, 1);
            and2->connect(or1, 0);

            or1_old = or1;
        }

        Indicator * Cout = new Indicator;
        or1->connect(Cout);

        // Test 1
        registerA.at(0)->setState(Signal::HIGH);
        registerA.at(1)->setState(Signal::LOW);
        registerA.at(2)->setState(Signal::LOW);

        registerB.at(0)->setState(Signal::LOW);
        registerB.at(1)->setState(Signal::HIGH);
        registerB.at(2)->setState(Signal::LOW);

        evaluate(registerS.at(0)->getState() == Signal::HIGH);
        evaluate(registerS.at(1)->getState() == Signal::HIGH);
        evaluate(registerS.at(2)->getState() == Signal::LOW);

        evaluate(Cout->getState() == Signal::LOW);

        // Test 2
        registerA.at(0)->setState(Signal::LOW);
        registerA.at(1)->setState(Signal::LOW);
        registerA.at(2)->setState(Signal::LOW);

        registerB.at(0)->setState(Signal::LOW);
        registerB.at(1)->setState(Signal::LOW);
        registerB.at(2)->setState(Signal::LOW);

        evaluate(registerS.at(0)->getState() == Signal::LOW);
        evaluate(registerS.at(1)->getState() == Signal::LOW);
        evaluate(registerS.at(2)->getState() == Signal::LOW);

        evaluate(Cout->getState() == Signal::LOW);

        // Test 3
        registerA.at(0)->setState(Signal::HIGH);
        registerA.at(1)->setState(Signal::HIGH);
        registerA.at(2)->setState(Signal::HIGH);

        registerB.at(0)->setState(Signal::HIGH);
        registerB.at(1)->setState(Signal::HIGH);
        registerB.at(2)->setState(Signal::HIGH);

        evaluate(registerS.at(0)->getState() == Signal::LOW);
        evaluate(registerS.at(1)->getState() == Signal::HIGH);
        evaluate(registerS.at(2)->getState() == Signal::HIGH);

        evaluate(Cout->getState() == Signal::HIGH);

        // Test 4
        registerA.at(0)->setState(Signal::HIGH);
        registerA.at(1)->setState(Signal::HIGH);
        registerA.at(2)->setState(Signal::LOW);

        registerB.at(0)->setState(Signal::LOW);
        registerB.at(1)->setState(Signal::LOW);
        registerB.at(2)->setState(Signal::HIGH);

        evaluate(registerS.at(0)->getState() == Signal::HIGH);
        evaluate(registerS.at(1)->getState() == Signal::HIGH);
        evaluate(registerS.at(2)->getState() == Signal::HIGH);

        evaluate(Cout->getState() == Signal::LOW);

        // Test 5
        registerA.at(0)->setState(Signal::HIGH);
        registerA.at(1)->setState(Signal::HIGH);
        registerA.at(2)->setState(Signal::LOW);

        registerB.at(0)->setState(Signal::HIGH);
        registerB.at(1)->setState(Signal::LOW);
        registerB.at(2)->setState(Signal::HIGH);

        evaluate(registerS.at(0)->getState() == Signal::LOW);
        evaluate(registerS.at(1)->getState() == Signal::LOW);
        evaluate(registerS.at(2)->getState() == Signal::LOW);

        evaluate(Cout->getState() == Signal::HIGH);
    }
}


void DigitalCircuitsTest::testUnstableCircuits(void)
{
    cout << "     ===== DigitalCircuitsTest::testUnstableCircuits =====" << endl;

    // unstable circuits causing a continuous cycle of evaluation

    {
        cout << "     ===== 1 =====" << endl;

        // oscillator

        GateXOR * gateXor = new GateXOR;
        SignalSource * src = new SignalSource;
        Indicator * ind = new Indicator;

        src->connect(gateXor, 0);
        gateXor->connect(ind);
        gateXor->connect(gateXor, 1);

        src->setState(Signal::HIGH);
    }

    {
        cout << "     ===== 2 =====" << endl;

        // latching

        SignalSource * src = new SignalSource;
        PushButton * pb = new PushButton;
        GateAND * gateAnd = new GateAND;
        GateXOR * gateXor = new GateXOR;
        Indicator * ind = new Indicator;

        src->connect(gateAnd, 0);
        src->connect(pb);
        pb->connect(gateXor, 0);
        gateXor->connect(gateAnd, 1);
        gateAnd->connect(gateXor, 1);
        gateAnd->connect(ind);

        src->setState(Signal::HIGH);
        evaluate(ind->getState() == Signal::LOW);

        pb->push();
        evaluate(ind->getState() == Signal::HIGH);

        pb->push();
        evaluate(ind->getState() == Signal::LOW);
    }
}


void DigitalCircuitsTest::testManualTests()
{
    cout << "     ===== DigitalCircuitsTest::testManualTests =====" << endl;

    GateAND * gateAnd1 = new GateAND;
    cout << gateAnd1->toString() << endl;
    GateAND * gateAnd2 = new GateAND("gateAnd2");
    cout << gateAnd2->toString() << endl;
    GateAND * gateAnd3 = new GateAND(3);
    cout << gateAnd3->toString() << endl;
    GateAND * gateAnd4 = new GateAND(4, "gateAnd4");
    cout << gateAnd4->toString() << endl;
    //    GateAND * gateAnd5 = new GateAND(1); // exception

    GateOR * gateOr1 = new GateOR;
    cout << gateOr1->toString() << endl;
    GateOR * gateOr2 = new GateOR("gateOr2");
    cout << gateOr2->toString() << endl;
    GateOR * gateOr3 = new GateOR(3);
    cout << gateOr3->toString() << endl;
    GateOR * gateOr4 = new GateOR(4, "gateOr4");
    cout << gateOr4->toString() << endl;

    GateXOR * gateXor1 = new GateXOR;
    cout << gateXor1->toString() << endl;
    GateXOR * gateXor2 = new GateXOR("gateXor2");
    cout << gateXor2->toString() << endl;
    GateXOR * gateXor3 = new GateXOR(3);
    cout << gateXor3->toString() << endl;
    GateXOR * gateXor4 = new GateXOR(4, "gateXor4");
    cout << gateXor4->toString() << endl;


    Indicator * ind1 = new Indicator;
    cout << ind1->toString() << endl;
    Indicator * ind2 = new Indicator("ind2");
    cout << ind2->toString() << endl;
    Indicator * ind3 = new Indicator(1);
    cout << ind3->toString() << endl;
    Indicator * ind4 = new Indicator(4, "ind4");
    cout << ind4->toString() << endl;

    Input * inp1 = new Input;
    Input * inp2 = new Input(gateAnd1);
    Input * inp3 = new Input(gateOr1);
    Input * inp4 = new Input(ind4);
    //    Input * inp5 = new Input(src1); // illegal


    SignalSource * src1 = new SignalSource;
    cout << src1->toString() << endl;
    SignalSource * src2 = new SignalSource("src2");
    cout << src2->toString() << endl;

    cout << "##################" << endl;

    src2->connect(gateAnd4);
    src2->connect(gateOr4, 1);
    src2->connect(gateXor4, 3);
    src2->connect(ind4, 1);
    src2->setState(1);
    cout << src2->toString() << endl;
    cout << gateAnd4->toString() << endl;
    cout << gateOr4->toString() << endl;
    cout << gateXor4->toString() << endl;
    cout << ind4->toString() << endl;

    //    AbstractComponent * ac = new AbstractComponent; // illegal
    //    AbstractInputComponent * ic = new AbstractInputComponent; // illegal
    AbstractOutputComponent * oc = new AbstractOutputComponent; // SHOULD be illegal !
    //    AbstractIOComponent * ioc = new AbstractIOComponent; // illegal
    //    AbstractGate * ag = new AbstractGate; // illegal
}
