#ifndef ABSTRACTGATE_H
#define ABSTRACTGATE_H

#include "abstractiocomponent.h"


class AbstractGate : public AbstractIOComponent
{
    public:

        AbstractGate(const std::string & name = "");
        AbstractGate(const unsigned int numberOfInputs,
                     const std::string & name = "");
};

#endif // ABSTRACTGATE_H
