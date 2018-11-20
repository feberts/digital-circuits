#include "gatexor.h"


Signal::SignalState GateXOR::evaluateState(void) const
{
    unsigned int count = 0;

    for(Input const * const input : mInputs)
    {
        if(input->getState() == Signal::HIGH)
        {
            count++;
        }
    }

    if(count == 1)
    {
        return Signal::HIGH;
    }
    else
    {
        return Signal::LOW;
    }
}
