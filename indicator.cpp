#include "indicator.h"


Signal::SignalState Indicator::getState(void) const
{
    return mState;
}


Signal::SignalState Indicator::evaluateState(void) const
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
