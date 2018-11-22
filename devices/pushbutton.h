#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "../abstracts/abstractiocomponent.h"


class PushButton : public AbstractIOComponent
{
    public:

        PushButton(const std::string & name = "");

        void push(void);

    protected:

        virtual Signal::SignalState evaluateState(void) const override;
        virtual void evaluate(void) override;

        Signal::SignalState mSwitchState;
};

#endif // PUSHBUTTON_H
