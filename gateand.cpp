#include "gateand.h"


Signal::SignalState GateAND::evaluateOutput(void) const
{
    Signal::SignalState newOutputState = Signal::HIGH;

    for(const DigitalInput & input : mInputs)
    {
        if(input.getState() == Signal::LOW)
        {
            newOutputState = Signal::LOW;
        }
    }

    return newOutputState;
}


