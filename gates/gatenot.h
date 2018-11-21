#ifndef GATENOT_H
#define GATENOT_H

#include "../abstracts/abstractiocomponent.h"


class GateNOT : public AbstractIOComponent
{
    public:

        GateNOT(const std::string & name = "");

    protected:

        virtual Signal::SignalState evaluateState(void) const override;
};

#endif // GATENOT_H
