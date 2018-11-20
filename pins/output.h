#ifndef OUTPUT_H
#define OUTPUT_H

#include <set>
#include "../globals/signal.h"

class Input;


class Output
{
        friend Input;

    public:

        Output(void);
        ~Output();

        void setState(const Signal::SignalState newState);
        Signal::SignalState getState(void) const;

        void connect(Input * const input);
        void disconnect(Input * const input);

    protected:

        void disconnectFromDeletedInput(Input * const input); // called in Input::~Input
        void disconnectCheck(Input * const input) const;

        void emitSignal(void) const;

        Signal::SignalState mState;
        std::set<Input *> mConnectedInputs;
};

#endif // OUTPUT_H
