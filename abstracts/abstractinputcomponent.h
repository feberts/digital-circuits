#ifndef ABSTRACTINPUTCOMPONENT_H
#define ABSTRACTINPUTCOMPONENT_H

#include <vector>
#include "abstractcomponent.h"
#include "../pins/input.h"

class AbstractOutputComponent;


class AbstractInputComponent : public AbstractComponent
{
        friend AbstractOutputComponent;

    public:

        AbstractInputComponent(const std::string & name = "");
        AbstractInputComponent(const unsigned int numberOfInputs,
                               const std::string & name = "");

        virtual ~AbstractInputComponent(void);

        Signal::SignalState getState(void) const;

        virtual void evaluate(void);
        virtual std::string toString(void) const override;

    protected:

        virtual Signal::SignalState evaluateState(void) const = 0;

        std::vector<Input *> mInputs;
        Signal::SignalState mState;
};

#endif // ABSTRACTINPUTCOMPONENT_H
