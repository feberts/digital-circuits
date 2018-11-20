#ifndef ABSTRACTIOCOMPONENT_H
#define ABSTRACTIOCOMPONENT_H

#include "abstractinputcomponent.h"
#include "abstractoutputcomponent.h"


class AbstractIOComponent :
        public AbstractOutputComponent, // Mind the order of construction !
        public AbstractInputComponent   // 'Inputs' must be destroyed FIRST !
{
        using AbstractInputComponent::AbstractInputComponent;

    public:

        void setState(const Signal::SignalState) = delete;
        using AbstractOutputComponent::getState;

        virtual void evaluate(void) override;
        using AbstractInputComponent::toString;
};

#endif // ABSTRACTIOCOMPONENT_H
