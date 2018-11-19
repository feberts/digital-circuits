#ifndef DIGITALCIRCUITSTEST_H
#define DIGITALCIRCUITSTEST_H


class DigitalCircuitsTest
{
    public:

        DigitalCircuitsTest() = default;

        void testAll(void);

        void testInputsOutputs(void);
        void testIndicator(void);
        void testSignalSource(void);
        void testSignalSourceIndicator(void);
        void testGateAND(void);
        void testGateOR(void);
        void testGateConnect(void);
        void testGateDisconnect(void);
        void testGateDelete(void);

    protected:

        bool evaluate(const bool testResult);
        bool mError = false;
};

#endif // DIGITALCIRCUITSTEST_H
