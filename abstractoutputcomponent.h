#ifndef ABSTRACTOUTPUTCOMPONENT_H
#define ABSTRACTOUTPUTCOMPONENT_H

#include "abstractcomponent.h"
#include "output.h"

class AbstractInputComponent;


class AbstractOutputComponent : public AbstractComponent
{
    public:

        AbstractOutputComponent(const std::string & name = "");
        virtual ~AbstractOutputComponent(void);

        void connect(AbstractInputComponent * const inputComponent, const unsigned int inputIndex = 0);
        void disConnect(AbstractInputComponent * const inputComponent, const unsigned int inputIndex = 0);

        virtual std::string toString(void) const override;

    protected:

        Output * mOutput;
};

#endif // ABSTRACTOUTPUTCOMPONENT_H