#include "gateand.h"


Signal::SignalState GateAND::evaluateState(void) const
{
    Signal::SignalState newOutputState = Signal::HIGH;

    for(DigitalInput const * const input : mInputs)
    {
        if(input->getState() == Signal::LOW)
        {
            newOutputState = Signal::LOW;
        }
    }

    return newOutputState;
}


