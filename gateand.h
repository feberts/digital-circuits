#ifndef GATEAND_H
#define GATEAND_H

#include "abstractlogicgate.h"


class GateAND : public AbstractLogicGate
{
        using AbstractLogicGate::AbstractLogicGate;

    protected:

        virtual Signal::SignalState evaluateOutput(void) const override;
};

#endif // GATEAND_H
