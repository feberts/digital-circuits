#include "gateor.h"


Signal::SignalState GateOR::evaluateState(void) const
{
    Signal::SignalState newOutputState = Signal::LOW;

    for(Input const * const input : mInputs)
    {
        if(input->getState() == Signal::HIGH)
        {
            newOutputState = Signal::HIGH;
        }
    }

    return newOutputState;
}
