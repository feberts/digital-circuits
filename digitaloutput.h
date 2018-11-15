#ifndef DIGITALOUTPUT_H
#define DIGITALOUTPUT_H

#include <map>
#include <set>

#include "signal.h"
class AbstractLogicGate;

class DigitalOutput
{
    public:

        DigitalOutput() = delete;
        DigitalOutput(AbstractLogicGate * const parentGate);

        ~DigitalOutput();

        void setState(const Signal::SignalState newState);
        Signal::SignalState getOutputState(void) const;

        void connect(AbstractLogicGate * const otherGate,
                     const unsigned int otherInputIndex);
        void disConnect(AbstractLogicGate * const otherGate,
                        const unsigned int otherInputIndex,
                        const bool otherGateDeleted = false);

    protected:

        void emitOutputSignal(const Signal::SignalState signalState) const;

        AbstractLogicGate * mParentGate;
        Signal::SignalState mOutputState;
        std::map<AbstractLogicGate *, std::set<unsigned int>> mConnectionsToOtherGates;
};

#endif // DIGITALOUTPUT_H
