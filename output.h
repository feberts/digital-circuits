#ifndef OUTPUT_H
#define OUTPUT_H

#include <map>
#include <set>

#include "signal.h"
class AbstractGate;

class Output
{
    public:

        Output() = delete;
        Output(AbstractGate * const parentGate);

        ~Output();

        void setState(const Signal::SignalState newState);
        Signal::SignalState getOutputState(void) const;

        void connect(AbstractGate * const otherGate,
                     const unsigned int otherInputIndex);
        void disConnect(AbstractGate * const otherGate,
                        const unsigned int otherInputIndex,
                        const bool otherGateDeleted = false);

    protected:

        void emitOutputSignal(const Signal::SignalState signalState) const;

        AbstractGate * mParentGate;
        Signal::SignalState mOutputState;
        std::map<AbstractGate *, std::set<unsigned int>> mConnectionsToOtherGates;
};

#endif // OUTPUT_H
