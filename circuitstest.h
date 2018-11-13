#ifndef CIRCUITSTEST_H
#define CIRCUITSTEST_H


class CircuitsTest
{
    public:

        CircuitsTest() = default;

        void testAll(void) const;

        void testGateAND(void) const;
        void testGateConnections(void) const;
};

#endif // CIRCUITSTEST_H
