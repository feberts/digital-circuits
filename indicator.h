#ifndef INDICATOR_H
#define INDICATOR_H

#include "abstractinputcomponent.h"


class Indicator : public AbstractInputComponent
{
        using AbstractInputComponent::AbstractInputComponent;

    public:

        Signal::SignalState getState(void) const;

    protected:

        virtual Signal::SignalState evaluateState(void) const override;
};

#endif // INDICATOR_H
