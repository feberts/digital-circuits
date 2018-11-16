#ifndef INPUT_H
#define INPUT_H

#include <set>
#include "signal.h"

class Output;

class AbstractGate;


class Input
{
    public:

        Input(void);
        Input(AbstractGate * const parentGate, const unsigned int inputIndex = 0);

        ~Input(void);

        void setState(const Signal::SignalState newState);
        Signal::SignalState getState(void) const;

        void connect(AbstractGate * const otherGate);
        void disconnect(AbstractGate * const otherGate);

        void connect(Output * const output);
        void disconnect(Output * const output);

    protected:


        AbstractGate * mParentGate;
        Signal::SignalState mInputState;
        std::set<AbstractGate *> mConnectionsFromOtherGates;
        unsigned int mInputIndex;
};

#endif // INPUT_H