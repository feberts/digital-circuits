#include "input.h"

#include <stdexcept>
#include "abstractgate.h"

using namespace std;


Input::Input(AbstractGate * const parentGate, const unsigned int inputIndex)
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

Input::~Input()
{
    for(AbstractGate * connectedGate : mConnectionsFromOtherGates)
    {
        connectedGate->disConnectFromDeletedGate(mParentGate, mInputIndex);
    }
}


void Input::setState(const Signal::SignalState newState)
{
    if(mInputState != newState)
    {
        mInputState = newState;

        if(mInputState == Signal::LOW)
        {
            for(AbstractGate * connectedGate : mConnectionsFromOtherGates)
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


Signal::SignalState Input::getState(void) const
{
    return mInputState;
}


void Input::connectToOutput(AbstractGate * const otherGate)
{
    if(!otherGate)
    {
        throw invalid_argument("DigitalInput::connectToOutput : otherGate is null");
    }

    mConnectionsFromOtherGates.insert(otherGate);
}

void Input::disConnectFromOutput(AbstractGate * const otherGate)
{
    if(!otherGate)
    {
        throw invalid_argument("AbstractLogicGate::disConnect : otherGate is null");
    }

    mConnectionsFromOtherGates.erase(otherGate);
}
