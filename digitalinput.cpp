#include "digitalinput.h"

#include <stdexcept>
#include "abstractlogicgate.h"

using namespace std;


DigitalInput::DigitalInput(AbstractLogicGate * const parentGate, const unsigned int inputIndex)
    : mParentGate(parentGate),
      mInputState(Signal::LOW),
      mConnectionsFromOtherGates({}),
      mInputIndex(inputIndex)
{
    if(!mParentGate)
    {
        throw std::invalid_argument("DigitalInput::DigitalInput : parentGate is null");
    }
}

DigitalInput::~DigitalInput()
{
    for(AbstractLogicGate * connectedGate : mConnectionsFromOtherGates)
    {
        connectedGate->disConnectFromDeletedGate(mParentGate, mInputIndex);
    }
}


void DigitalInput::setState(const Signal::SignalState newState)
{
    if(mInputState != newState)
    {
        mInputState = newState;

        if(mInputState == Signal::LOW)
        {
            for(AbstractLogicGate * connectedGate : mConnectionsFromOtherGates)
            {
                if(connectedGate->getOutputState() == Signal::HIGH)
                {
                    mInputState = Signal::HIGH;
                }
            }
        }

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
