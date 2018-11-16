#ifndef CIRCUITSTEST_H
#define CIRCUITSTEST_H


class CircuitsTest
{
    public:

        CircuitsTest() = default;

        void testAll(void) const;

        void testGateAND(void) const;
        void testGateConnect(void) const;
        void testGateDisconnect(void) const;
        void testGateDelete(void) const;

    protected:

        void evaluate(const bool testResult);
        bool mError = false;
};

#endif // CIRCUITSTEST_H
