#include "output.h"

#include <stdexcept>
#include <set>
#include "abstractgate.h"

using namespace std;

typedef pair<AbstractGate *, set<unsigned int>> pairGateInputset;


Output::Output(AbstractGate * const parentGate)
    : mParentGate(parentGate),
      mOutputState(Signal::LOW),
      mConnectionsToOtherGates({})
{
    if(!mParentGate)
    {
        throw std::invalid_argument("DigitalOutput::DigitalOutput : parentGate is null");
    }
}

Output::~Output()
{
    mOutputState = Signal::LOW;
    emitOutputSignal(Signal::LOW);

    for(auto gate = mConnectionsToOtherGates.cbegin(); gate != mConnectionsToOtherGates.cend(); ++gate)
    {
        for(auto input = gate->second.cbegin(); input != gate->second.cend(); ++input)
        {
            gate->first->disConnectFromOutput(mParentGate, *input);
        }
    }

}


void Output::setState(const Signal::SignalState newState)
{
    if(mOutputState != newState)
    {
        mOutputState = newState;
        emitOutputSignal(mOutputState);
    }
}


Signal::SignalState Output::getOutputState(void) const
{
    return mOutputState;
}


void Output::connect(AbstractGate * const otherGate,
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

void Output::disConnect(AbstractGate * const otherGate,
                               const unsigned int otherInputIndex,
                               const bool otherGateDeleted)
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

            if(!otherGateDeleted)
            {
                otherGate->disConnectFromOutput(mParentGate, otherInputIndex);
                otherGate->setInputState(otherInputIndex, Signal::LOW);
            }
        }
    }
}

void Output::emitOutputSignal(const Signal::SignalState signalState) const
{
    for(auto gate = mConnectionsToOtherGates.cbegin(); gate != mConnectionsToOtherGates.cend(); ++gate)
    {
        for(auto input = gate->second.cbegin(); input != gate->second.cend(); ++input)
        {
            gate->first->setInputState(*input, signalState);
        }
    }
}
