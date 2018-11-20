#ifndef ABSTRACTCOMPONENT_H
#define ABSTRACTCOMPONENT_H

#include <string>


class AbstractComponent
{
    public:

        AbstractComponent(const std::string & name);

        std::string getName(void) const;

        virtual std::string toString(void) const = 0;

    protected:

        std::string mName;
};

#endif // ABSTRACTCOMPONENT_H
