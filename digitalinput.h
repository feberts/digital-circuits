#ifndef DIGITALINPUT_H
#define DIGITALINPUT_H

#include "signal.h"

class AbstractLogicGate;


class DigitalInput
{
    public:

        DigitalInput() = delete;
        DigitalInput(AbstractLogicGate * const parentGate);

        void setState(const Signal::SignalState newState);
        Signal::SignalState getState(void) const;

    protected:

        AbstractLogicGate * mParentGate;
        Signal::SignalState mInputState;
};

#endif // DIGITALINPUT_H
