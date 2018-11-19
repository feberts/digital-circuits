#ifndef ABSTRACTINPUTCOMPONENT_H
#define ABSTRACTINPUTCOMPONENT_H

#include <vector>
#include "abstractcomponent.h"
#include "input.h"

class AbstractOutputComponent;


class AbstractInputComponent : public AbstractComponent
{
        friend AbstractOutputComponent;

    public:

        AbstractInputComponent(const std::string & name = "");
        AbstractInputComponent(const unsigned int numberOfInputs,
                               const std::string & name = "");

        virtual ~AbstractInputComponent(void);

        virtual void evaluate(void); // todo = 0
        virtual std::string toString(void) const override;

    protected:

        virtual Signal::SignalState evaluateState(void) const = 0;

        std::vector<Input *> mInputs;
        Signal::SignalState mState;
};

#endif // ABSTRACTINPUTCOMPONENT_H
