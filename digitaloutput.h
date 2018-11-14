#ifndef DIGITALOUTPUT_H
#define DIGITALOUTPUT_H

#include "signal.h"

class DigitalOutput
{
        DigitalOutput(void);

        void setState(const Signal::SignalState newState);
        Signal::SignalState getOutputState(void) const;

    protected:

        Signal::SignalState mOuputState;
};

#endif // DIGITALOUTPUT_H
