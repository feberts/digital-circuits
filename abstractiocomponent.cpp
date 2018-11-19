#include "abstractiocomponent.h"

using namespace std;


std::string AbstractIOComponent::toString(void) const
{
    if(AbstractInputComponent::mName.empty())
    {
        return "";
    }

    string retStr = "=== " + AbstractInputComponent::mName + " ===\n";

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


void AbstractIOComponent::evaluate(void)
{
    mState = evaluateState();
    mOutput->setState(mState);
}
