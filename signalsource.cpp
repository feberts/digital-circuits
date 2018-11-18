#include "signalsource.h"


void SignalSource::setState(const Signal::SignalState newState)
{
    mOutput->setState(newState);
}


Signal::SignalState SignalSource::getState(void) const
{
    return mOutput->getState();
}
