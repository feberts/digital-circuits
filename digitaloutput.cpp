#include "digitaloutput.h"

#include <stdexcept>
#include <set>
#include "abstractlogicgate.h"

using namespace std;

typedef pair<AbstractLogicGate *, set<unsigned int>> pairGateInputset;


DigitalOutput::DigitalOutput(AbstractLogicGate * const parentGate)
    : mParentGate(parentGate),
      mOutputState(Signal::LOW),
      mConnectionsToOtherGates({})
{
    if(!mParentGate)
    {
        throw std::invalid_argument("DigitalOutput::DigitalOutput : parentGate is null");
    }
}



void DigitalOutput::setState(const Signal::SignalState newState)
{
    if(mOutputState != newState)
    {
        mOutputState = newState;
        emitOutputSignal(mOutputState); // todo : nötig mit parameter ?
    }
}


Signal::SignalState DigitalOutput::getOutputState(void) const
{
    return mOutputState;
}


void DigitalOutput::connect(AbstractLogicGate * const otherGate,
                                const unsigned int otherInputIndex)
{
        auto gate = mConnectionsToOtherGates.find(otherGate);

        if(gate == mConnectionsToOtherGates.end()) // not yet connected to otherGate
        {
            set<unsigned int> inputSet;
            inputSet.insert(otherInputIndex);

            mConnectionsToOtherGates.insert(pairGateInputset(otherGate, inputSet));
        }
        else // already connected to at least one input of otherGate
        {
            gate->second.insert(otherInputIndex);
        }

        otherGate->connectToOutput(mParentGate, otherInputIndex);

        emitOutputSignal(mOutputState); // todo nötig ?
}

void DigitalOutput::disConnect(AbstractLogicGate * const otherGate,
                                   const unsigned int otherInputIndex)
{
    auto gate = mConnectionsToOtherGates.find(otherGate);

    if(gate == mConnectionsToOtherGates.end()) // no connections to otherGate found
    {
        throw invalid_argument("AbstractLogicGate::disConnect : not connected to otherGate");
    }
    else // connected to at least one input of otherGate
    {
        auto input = gate->second.find(otherInputIndex);

        if(input == gate->second.end()) // not connected to this specific input
        {
            throw invalid_argument("AbstractLogicGate::disConnect : not connected to this specific input");
        }
        else // connected to this specific input
        {
            gate->second.erase(otherInputIndex);

            if(gate->second.empty()) // remove otherGate completely if all inputs are disconnected
            {
                mConnectionsToOtherGates.erase(otherGate);
            }

            otherGate->disConnectFromOutput(mParentGate, otherInputIndex);
            otherGate->setInputState(otherInputIndex, Signal::LOW);
        }
    }
}

void DigitalOutput::emitOutputSignal(const Signal::SignalState signalState) const
{
    for(auto gate = mConnectionsToOtherGates.cbegin(); gate != mConnectionsToOtherGates.cend(); ++gate)
    {
        for(auto input = gate->second.cbegin(); input != gate->second.cend(); ++input)
        {
            gate->first->setInputState(*input, signalState);
        }
    }
}
