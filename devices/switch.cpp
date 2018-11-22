#include "switch.h"

using namespace std;

const unsigned int MIN_INPUTS = 1;


Switch::Switch(const string & name)
    : AbstractIOComponent(MIN_INPUTS, name),
      mSwitchState(Signal::OFF)
{ }


void Switch::toogle(const Signal::SignalState newSwitchState)
{
    mSwitchState = newSwitchState;
    evaluate();
}


Signal::SignalState Switch::evaluateState(void) const
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
