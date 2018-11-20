#ifndef ABSTRACTOUTPUTCOMPONENT_H
#define ABSTRACTOUTPUTCOMPONENT_H

#include "abstractcomponent.h"
#include "../pins/output.h"

class AbstractInputComponent;


class AbstractOutputComponent : public AbstractComponent
{
    public:

        AbstractOutputComponent(const std::string & name = "");
        virtual ~AbstractOutputComponent(void);

        void connect(AbstractInputComponent const * const inputComponent,
                     const unsigned int inputIndex = 0);
        void disconnect(AbstractInputComponent const * const inputComponent,
                        const unsigned int inputIndex = 0);

        void setState(const Signal::SignalState newState);
        Signal::SignalState getState(void) const;

        virtual std::string toString(void) const override;

    protected:

        Output * mOutput;
};

#endif // ABSTRACTOUTPUTCOMPONENT_H
