#ifndef OUTPUT_H
#define OUTPUT_H

#include <map>
#include <set>

#include "signal.h"
class Input;

class AbstractGate;

class Output
{
    public:

        Output(void);
        Output(AbstractGate * const parentGate);

        ~Output();

        void setState(const Signal::SignalState newState);
        Signal::SignalState getState(void) const;

        void connect(AbstractGate * const otherGate,
                     const unsigned int otherInputIndex);
        void disconnect(AbstractGate * const otherGate,
                        const unsigned int otherInputIndex,
                        const bool otherGateDeleted = false);

        void connect(Input * const input);
        void disconnect(Input * const input);

    protected:

        void emitOutputSignal(const Signal::SignalState signalState) const;

        AbstractGate * mParentGate;
        Signal::SignalState mOutputState;
        std::map<AbstractGate *, std::set<unsigned int>> mConnectionsToOtherGates;
};

#endif // OUTPUT_H
