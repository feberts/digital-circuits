#include "digitaloutput.h"

#include <stdexcept>
#include "abstractlogicgate.h"

DigitalOutput::DigitalOutput(void)
    : mOuputState(Signal::LOW),
      mConnectionsToOtherGates({})
{ }


void DigitalOutput::setState(const Signal::SignalState newState)
{
    if(mOuputState != newState)
    {
        mOuputState = newState;
        emitOutputSignal(mOuputState); // todo : nötig mit parameter ?
    }
}


Signal::SignalState DigitalOutput::getOutputState(void) const
{
    return mOuputState;
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
