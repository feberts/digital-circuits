#ifndef GATENAND_H
#define GATENAND_H

#include "abstracts/abstractgate.h"


class GateNAND : public AbstractGate
{
    using AbstractGate::AbstractGate;

    protected:

        virtual Signal::SignalState evaluateState(void) const override;
};

#endif // GATENAND_H
