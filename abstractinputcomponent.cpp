#include "abstractinputcomponent.h"

#include <stdexcept>
#include "abstractoutputcomponent.h"

using namespace std;

const unsigned int MIN_INPUTS = 1;


AbstractInputComponent::AbstractInputComponent(const string & name)
    : AbstractInputComponent(MIN_INPUTS, name)
{ }


AbstractInputComponent::AbstractInputComponent(const unsigned int numberOfInputs,
                                               const string & name)
    : AbstractComponent(name),
      mInputs({}),
      mState(Signal::LOW)
{
    if(numberOfInputs < MIN_INPUTS)
    {
        throw invalid_argument("AbstractInputComponent::AbstractInputComponent "
                               ": numberOfInputs must be > "
                               + to_string(MIN_INPUTS));
    }

    for(unsigned int index = 0; index < numberOfInputs; index++)
    {
        mInputs.push_back(new Input(this));
    }
}


AbstractInputComponent::~AbstractInputComponent(void)
{
    for(Input * input : mInputs)
    {
        delete input;
    }
}


void AbstractInputComponent::evaluate()
{
    mState = evaluateState();
}


std::string AbstractInputComponent::toString(void) const
{
    if(mName.empty())
    {
        return "";
    }

    string retStr = "=== " + mName + " ===\n";

    for(unsigned int index = 0; index < mInputs.size(); index++)
    {
        retStr += "Input[" + to_string(index) + "] : ";
        retStr += (mInputs.at(index)->getState() == Signal::HIGH) ? "HIGH" : "LOW";
        retStr += "\n";
    }

    retStr += "State : ";
    retStr += (mState == Signal::HIGH) ? "HIGH" : "LOW";

    return retStr;
}
