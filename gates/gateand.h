#ifndef GATEAND_H
#define GATEAND_H

#include "../abstracts/abstractgate.h"


class GateAND : public AbstractGate
{
        using AbstractGate::AbstractGate;

    protected:

        virtual Signal::SignalState evaluateState(void) const override;
};

#endif // GATEAND_H
