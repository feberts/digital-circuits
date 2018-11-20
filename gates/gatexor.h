#ifndef GATEXOR_H
#define GATEXOR_H

#include "../abstracts/abstractgate.h"


class GateXOR : public AbstractGate
{
        using AbstractGate::AbstractGate;

    protected:

        virtual Signal::SignalState evaluateState(void) const override;
};

#endif // GATEXOR_H
