#ifndef DIGITALOUTPUT_H
#define DIGITALOUTPUT_H

#include <map>
#include <set>

#include "signal.h"
class AbstractLogicGate;

class DigitalOutput
{
    public:

        DigitalOutput(void);

        void setState(const Signal::SignalState newState);
        Signal::SignalState getOutputState(void) const;

    protected:

        void emitOutputSignal(const Signal::SignalState signalState) const;

        Signal::SignalState mOuputState;
        std::map<AbstractLogicGate *, std::set<unsigned int>> mConnectionsToOtherGates;
};

#endif // DIGITALOUTPUT_H
