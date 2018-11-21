#include "gatenand.h"

using namespace std;

const unsigned int MIN_INPUTS = 2;


GateNAND::GateNAND(const string & name)
    : GateNAND(MIN_INPUTS, name)
{ }


GateNAND::GateNAND(const unsigned int numberOfInputs,
                   const string & name)
    : AbstractGate(numberOfInputs, name)
{
    evaluate(); // workaround to put gate into correct initial state
}


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
