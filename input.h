#ifndef INPUT_H
#define INPUT_H

#include <set>
#include "signal.h"

class Output;
class AbstractGate;


class Input
{
        friend Output;

    public:

        Input(void);
        Input(AbstractGate * const parentComponent);

        ~Input(void);

        Signal::SignalState getState(void) const;

    protected:

        void updateState(void);

        void connect(Output * const output);
        void disconnect(Output * const output);

        AbstractGate * mParentComponent;
        Signal::SignalState mState;
        std::set<Output *> mConnectedOutputs;
};

#endif // INPUT_H
