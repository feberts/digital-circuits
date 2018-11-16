#ifndef ABSTRACTGATE_H
#define ABSTRACTGATE_H

#include <vector>
#include <map>
#include <set>
#include "abstractcomponent.h"
#include "input.h"
#include "output.h"


class AbstractGate : public AbstractComponent
{
    public:

        AbstractGate(const std::string & name = "");
        AbstractGate(const unsigned int numberOfInputs,
                          const std::string & name = "");

        virtual ~AbstractGate(void);

        void setInputState(const unsigned int inputIndex, const Signal::SignalState newState);
        Signal::SignalState getOutputState(void) const;

        void connect(AbstractGate * const otherGate, const unsigned int otherInputIndex);
        void disConnect(AbstractGate * const otherGate, const unsigned int otherInputIndex);

        void disConnectFromDeletedGate(AbstractGate * const otherGate, const unsigned int otherInputIndex);

        void evaluate(void);

        virtual std::string toString(void) const override;

        void connectToOutput(AbstractGate * const otherGate, const unsigned int inputIndex);
        void disConnectFromOutput(AbstractGate * const otherGate, const unsigned int inputIndex);

    protected:

        virtual Signal::SignalState evaluateState(void) const = 0;


        void checkConnection(AbstractGate * const otherGate,
                             const unsigned int otherInputIndex) const;



        unsigned int getNumberOfInputs(void) const;

        std::vector<Input *> mInputs;
        Output * mOutput;


        Signal::SignalState mGateState;
};

#endif // ABSTRACTGATE_H
