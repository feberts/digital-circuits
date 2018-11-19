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

        void evaluate(void) override;
        virtual std::string toString(void) const override;

};

#endif // ABSTRACTIOCOMPONENT_H
