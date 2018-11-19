#ifndef ABSTRACTIOCOMPONENT_H
#define ABSTRACTIOCOMPONENT_H

#include "abstractinputcomponent.h"
#include "abstractoutputcomponent.h"


class AbstractIOComponent :
        public AbstractOutputComponent, // Mind the order of construction !
        public AbstractInputComponent   // Inputs must be destructed FIRST !
{
        using AbstractInputComponent::AbstractInputComponent;

    public:

        virtual std::string toString(void) const override;

    protected:

        void evaluate(void) override;
};

#endif // ABSTRACTIOCOMPONENT_H
