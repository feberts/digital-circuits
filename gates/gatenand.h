#ifndef GATENAND_H
#define GATENAND_H

#include "abstracts/abstractgate.h"


class GateNAND : public AbstractGate
{
    public:

        GateNAND(const std::string & name = "");
        GateNAND(const unsigned int numberOfInputs,
                 const std::string & name = "");

    protected:

        virtual Signal::SignalState evaluateState(void) const override;
};

#endif // GATENAND_H
