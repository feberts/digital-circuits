#ifndef CIRCUITSTEST_H
#define CIRCUITSTEST_H


class CircuitsTest
{
    public:

        CircuitsTest() = default;

        void testAll(void);

        void testGateAND(void);
        void testGateConnect(void);
        void testGateDisconnect(void);
        void testGateDelete(void);

    protected:

        bool evaluate(const bool testResult);
        bool mError = false;
};

#endif // CIRCUITSTEST_H
