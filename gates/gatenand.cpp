#include "gatenand.h"


Signal::SignalState GateNAND::evaluateState() const
{
    for(Input const * const input : mInputs)
    {
        if(input->getState() == Signal::LOW)
        {
            return Signal::HIGH;
        }
    }

    return Signal::LOW;
}
