#include "gateand.h"


Signal::SignalState GateAND::evaluateState(void) const
{
    for(Input const * const input : mInputs)
    {
        if(input->getState() == Signal::LOW)
        {
            return Signal::LOW;
        }
    }

    return Signal::HIGH;
}


