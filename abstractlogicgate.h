#ifndef ABSTRACTLOGICGATE_H
#define ABSTRACTLOGICGATE_H

#include <vector>
#include <map>
#include <set>
#include "abstractcomponent.h"
#include "digitalinput.h"
#include "digitaloutput.h"


class AbstractLogicGate : public AbstractComponent
{
    public:

        AbstractLogicGate(const std::string & name = "");
        AbstractLogicGate(const unsigned int numberOfInputs,
                          const std::string & name = "");

        virtual ~AbstractLogicGate(void);

        void setInputState(const unsigned int inputIndex, const Signal::SignalState newState);
        Signal::SignalState getOutputState(void) const;

        void connect(AbstractLogicGate * const otherGate, const unsigned int otherInputIndex);
        void disConnect(AbstractLogicGate * const otherGate, const unsigned int otherInputIndex);

        void disConnectFromDeletedGate(AbstractLogicGate * const otherGate, const unsigned int otherInputIndex);

        void evaluate(void);

        virtual std::string toString(void) const override;

        void connectToOutput(AbstractLogicGate * const otherGate, const unsigned int inputIndex);
        void disConnectFromOutput(AbstractLogicGate * const otherGate, const unsigned int inputIndex);

    protected:

        virtual Signal::SignalState evaluateState(void) const = 0;


        void checkConnection(AbstractLogicGate * const otherGate,
                             const unsigned int otherInputIndex) const;



        unsigned int getNumberOfInputs(void) const;

        std::vector<DigitalInput *> mInputs;
        DigitalOutput * mOutput;


        Signal::SignalState mGateState;
};

#endif // ABSTRACTLOGICGATE_H
