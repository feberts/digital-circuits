#include "gatenot.h"

using namespace std;

const unsigned int MIN_INPUTS = 1;


GateNOT::GateNOT(const string & name)
    : AbstractIOComponent(MIN_INPUTS, name)
{
    evaluate();
}


Signal::SignalState GateNOT::evaluateState(void) const
{
    if(mInputs.at(0)->getState() == Signal::HIGH)
    {
        return Signal::LOW;
    }
    else
    {
        return Signal::HIGH;
    }
}

