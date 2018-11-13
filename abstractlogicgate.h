#ifndef ABSTRACTLOGICGATE_H
#define ABSTRACTLOGICGATE_H

#include <vector>
#include <map>
#include <set>
#include "abstractcomponent.h"
#include "digitalinput.h"


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

        unsigned int getNumberOfInputs(void) const;

        void evaluate(void);

        virtual std::string toString(void) const override;

    protected:

        virtual Signal::SignalState evaluateOutput(void) const = 0;
        void emitOutputSignal(const Signal::SignalState signalState); // todo: const ?

        void checkConnection(AbstractLogicGate * const otherGate,
                             const unsigned int otherInputIndex) const;

        std::vector<DigitalInput> mInputs;
        std::map<AbstractLogicGate *, std::set<unsigned int>> mConnectedGates;

        Signal::SignalState mOutputState;

};

#endif // ABSTRACTLOGICGATE_H
