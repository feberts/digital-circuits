#ifndef SIGNALSOURCE_H
#define SIGNALSOURCE_H

#include "abstractoutputcomponent.h"


class SignalSource : public AbstractOutputComponent
{
        using AbstractOutputComponent::AbstractOutputComponent;

    public:

        void setState(const Signal::SignalState newState);
        Signal::SignalState getState(void) const;
};

#endif // SIGNALSOURCE_H
