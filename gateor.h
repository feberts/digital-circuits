#ifndef GATEOR_H
#define GATEOR_H

#include "abstractgate.h"


class GateOR : public AbstractGate
{
        using AbstractGate::AbstractGate;

    protected:

        virtual Signal::SignalState evaluateState(void) const override;
};

#endif // GATEOR_H
