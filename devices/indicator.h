#ifndef INDICATOR_H
#define INDICATOR_H

#include "../abstracts/abstractinputcomponent.h"


class Indicator : public AbstractInputComponent
{
        using AbstractInputComponent::AbstractInputComponent;

    protected:

        virtual Signal::SignalState evaluateState(void) const override;
};

#endif // INDICATOR_H
