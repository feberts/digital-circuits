#include "gateor.h"


Signal::SignalState GateOR::evaluateState(void) const
{
    for(Input const * const input : mInputs)
    {
        if(input->getState() == Signal::HIGH)
        {
            return Signal::HIGH;
        }
    }

    return Signal::LOW;
}
