#include "digitaloutput.h"

#include <stdexcept>


DigitalOutput::DigitalOutput(void)
    : mOuputState(Signal::LOW)
{ }


void DigitalOutput::setState(const Signal::SignalState newState)
{
    if(mOuputState != newState)
    {
        mOuputState = newState;
        // todo an alle anderen angeschlossenen gates emittieren
    }
}


Signal::SignalState DigitalOutput::getOutputState(void) const
{
    return mOuputState;
}
