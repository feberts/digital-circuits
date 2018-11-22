#include "pushbutton.h"

using namespace std;

const unsigned int MIN_INPUTS = 1;


PushButton::PushButton(const string & name)
    : AbstractIOComponent(MIN_INPUTS, name),
      mSwitchState(Signal::OFF)
{ }


void PushButton::push(void)
{
    mSwitchState = Signal::ON;
    evaluate();
}


Signal::SignalState PushButton::evaluateState(void) const
{
    if(mInputs.at(0)->getState() == Signal::HIGH
       && mSwitchState == Signal::ON)
    {
        return Signal::HIGH;
    }
    else
    {
        return Signal::LOW;
    }
}


void PushButton::evaluate(void)
{
    mState = evaluateState();
    mOutput->setState(mState);

    mSwitchState = Signal::OFF;

    mState = evaluateState();
    mOutput->setState(mState);
}
