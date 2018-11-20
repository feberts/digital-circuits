#ifndef INPUT_H
#define INPUT_H

#include <set>
#include "../globals/signal.h"

class Output;
class AbstractInputComponent;


class Input
{
        friend Output;

    public:

        Input(void);
        Input(AbstractInputComponent * const parentComponent);

        ~Input(void);

        Signal::SignalState getState(void) const;

    protected:

        void updateState(void);

        void connect(Output * const output);
        void disconnect(Output * const output);

        AbstractInputComponent * mParentComponent;
        Signal::SignalState mState;
        std::set<Output *> mConnectedOutputs;
};

#endif // INPUT_H
