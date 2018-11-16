#ifndef INPUT_H
#define INPUT_H

#include <set>
#include "signal.h"

class AbstractGate;


class Input
{
    public:

        Input(void);
        Input(AbstractGate * const parentGate, const unsigned int inputIndex = 0);

        ~Input(void);

        void setState(const Signal::SignalState newState);
        Signal::SignalState getState(void) const;

        void connectToOutput(AbstractGate * const otherGate);
        void disConnectFromOutput(AbstractGate * const otherGate);

    protected:

        AbstractGate * mParentGate;
        Signal::SignalState mInputState;
        std::set<AbstractGate *> mConnectionsFromOtherGates;
        unsigned int mInputIndex;
};

#endif // INPUT_H
