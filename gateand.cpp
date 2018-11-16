#include "gateand.h"


Signal::SignalState GateAND::evaluateState(void) const
{
    Signal::SignalState newOutputState = Signal::HIGH;

    for(Input const * const input : mInputs)
    {
        if(input->getState() == Signal::LOW)
        {
            newOutputState = Signal::LOW;
        }
    }

    return newOutputState;
}


