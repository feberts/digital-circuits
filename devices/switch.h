#ifndef SWITCH_H
#define SWITCH_H

#include "../abstracts/abstractiocomponent.h"


class Switch : public AbstractIOComponent
{
    public:

        Switch(const std::string & name = "");

        void toogle(const Signal::SignalState newSwitchState);

    protected:

        virtual Signal::SignalState evaluateState(void) const override;

        Signal::SignalState mSwitchState;
};

#endif // SWITCH_H
