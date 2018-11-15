#ifndef DIGITALINPUT_H
#define DIGITALINPUT_H

#include <set>
#include "signal.h"

class AbstractLogicGate;


class DigitalInput
{
    public:

        DigitalInput(void) = delete;
        DigitalInput(AbstractLogicGate * const parentGate, const unsigned int inputIndex = 0);

        ~DigitalInput(void);

        void setState(const Signal::SignalState newState);
        Signal::SignalState getState(void) const;

        void connectToOutput(AbstractLogicGate * const otherGate);
        void disConnectFromOutput(AbstractLogicGate * const otherGate);

    protected:

        AbstractLogicGate * mParentGate;
        Signal::SignalState mInputState;
        std::set<AbstractLogicGate *> mConnectionsFromOtherGates;
        unsigned int mInputIndex;
};

#endif // DIGITALINPUT_H
