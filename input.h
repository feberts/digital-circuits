#ifndef INPUT_H
#define INPUT_H

#include <set>
#include "signal.h"

class Output;

class AbstractGate;


class Input
{
    public:

        Input(void);
        Input(AbstractGate * const parentGate);

        ~Input(void);

        void setState(const Signal::SignalState newState); // todo : protected ?
        Signal::SignalState getState(void) const;

        void connect(Output * const output); // todo : protected ?
        void disconnect(Output * const output); // todo : protected ?

    protected:


        AbstractGate * mParentGate;
        Signal::SignalState mInputState;
        std::set<Output *> mConnectedOutputs;
};

#endif // INPUT_H
