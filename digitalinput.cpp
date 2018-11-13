#include "digitalinput.h"

#include <stdexcept>
#include "abstractlogicgate.h"


DigitalInput::DigitalInput(AbstractLogicGate * const parentGate)
    : mParentGate(parentGate),
      mState(Signal::LOW)
{
    if(!mParentGate)
    {
        throw std::invalid_argument("DigitalInput::DigitalInput : parentGate is null");
    }
}


void DigitalInput::setState(const Signal::SignalState newState)
{
    if(mState != newState)
    {
        mState = newState;
        mParentGate->evaluate();
    }
}


Signal::SignalState DigitalInput::getState(void) const
{
    return mState;
}
