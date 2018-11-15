#include "digitalinput.h"

#include <stdexcept>
#include "abstractlogicgate.h"

using namespace std;


DigitalInput::DigitalInput(AbstractLogicGate * const parentGate)
    : mParentGate(parentGate),
      mInputState(Signal::LOW),
      mConnectionsFromOtherGates({})
{
    if(!mParentGate)
    {
        throw std::invalid_argument("DigitalInput::DigitalInput : parentGate is null");
    }
}


void DigitalInput::setState(const Signal::SignalState newState)
{
    if(mInputState != newState)
    {
        mInputState = newState;
        // todo alle anderen angeschlossenen gates abfragen
        mParentGate->evaluate();
    }
}


Signal::SignalState DigitalInput::getState(void) const
{
    return mInputState;
}


void DigitalInput::connectToOutput(AbstractLogicGate * const otherGate)
{
    if(!otherGate)
    {
        throw invalid_argument("DigitalInput::connectToOutput : otherGate is null");
    }

    mConnectionsFromOtherGates.insert(otherGate);
}

void DigitalInput::disConnectFromOutput(AbstractLogicGate * const otherGate)
{
    if(!otherGate)
    {
        throw invalid_argument("AbstractLogicGate::disConnect : otherGate is null");
    }

    mConnectionsFromOtherGates.erase(otherGate);
}
