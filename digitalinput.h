#ifndef DIGITALINPUT_H
#define DIGITALINPUT_H

#include <set>
#include "signal.h"

class AbstractLogicGate;


class DigitalInput
{
    public:

        DigitalInput() = delete;
        DigitalInput(AbstractLogicGate * const parentGate);

        void setState(const Signal::SignalState newState);
        Signal::SignalState getState(void) const;

        void connectToOutput(AbstractLogicGate * const otherGate);
        void disConnectFromOutput(AbstractLogicGate * const otherGate);

    protected:

        AbstractLogicGate * mParentGate;
        Signal::SignalState mInputState;
        std::set<AbstractLogicGate *> mConnectionsFromOtherGates;
};

#endif // DIGITALINPUT_H
