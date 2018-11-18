#include "abstractoutputcomponent.h"

#include <stdexcept>
#include "abstractinputcomponent.h"

using namespace std;


AbstractOutputComponent::AbstractOutputComponent(const string & name)
    : AbstractComponent(name),
      mOutput(new Output)
{ }


AbstractOutputComponent::~AbstractOutputComponent(void)
{
    delete mOutput;
}


void AbstractOutputComponent::connect(AbstractInputComponent * const inputComponent,
                                      const unsigned int inputIndex)
{
    if(!inputComponent)
    {
        throw invalid_argument("AbstractOutputComponent::connect : inputComponent is null");
    }

    try
    {
        mOutput->connect(inputComponent->mInputs.at(inputIndex));
    }
    catch(out_of_range)
    {
        throw invalid_argument("AbstractOutputComponent::connect : inputIndex invalid, no such input");
    }
}


void AbstractOutputComponent::disConnect(AbstractInputComponent * const inputComponent,
                                         const unsigned int inputIndex)
{
    if(!inputComponent)
    {
        throw invalid_argument("AbstractOutputComponent::disconnect : inputComponent is null");
    }

    try
    {
        mOutput->disconnect(inputComponent->mInputs.at(inputIndex));
    }
    catch(out_of_range)
    {
        throw invalid_argument("AbstractOutputComponent::disconnect : inputIndex invalid, no such input");
    }
}


std::string AbstractOutputComponent::toString(void) const
{
    if(mName.empty())
    {
        return "";
    }

    string retStr = "=== " + mName + " ===\n";

    retStr += "State : ";
    retStr += (mOutput->getState() == Signal::HIGH) ? "HIGH" : "LOW";

    return retStr;
}