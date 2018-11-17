#ifndef OUTPUT_H
#define OUTPUT_H

#include <map>
#include <set>

#include "signal.h"
class Input;


class Output
{
    public:

        Output(void);

        ~Output();

        void setState(const Signal::SignalState newState);
        Signal::SignalState getState(void) const; // todo : protected ?

        void connect(Input * const input);
        void disconnect(Input * const input);
        void disconnectFromDeletedInput(Input * const input);

    protected:

        void emitOutputSignal(void) const;

        Signal::SignalState mOutputState;
        std::set<Input *> mConnectedInputs;
};

#endif // OUTPUT_H
