#include "abstractgate.h"

#include <stdexcept>

using namespace std;


AbstractGate::AbstractGate(const string & name)
    : AbstractGate(2, name)
{ }


AbstractGate::AbstractGate(const unsigned int numberOfInputs,
                           const string & name)
    : AbstractComponent(name),
      mInputs({}),
      mOutput(new Output),
      mGateState(Signal::LOW)
{
//    if(numberOfInputs < 2)
//    {
//        throw invalid_argument("AbstractGate::AbstractGate : numberOfInputs must be > 1");
//    }

//    for(unsigned int index = 0; index < numberOfInputs; index++)
//    {
//        mInputs.push_back(new Input(this));
//    }
}


AbstractGate::~AbstractGate(void)
{
//    for(Input * input : mInputs)
//    {
//        delete input;
//    }

//    delete mOutput;
}


void AbstractGate::setInputState(const unsigned int inputIndex, const Signal::SignalState newState)
{
//    try
//    {
//        mInputs.at(inputIndex)->updateState();
//    }
//    catch(out_of_range)
//    {
//        throw invalid_argument("AbstractGate::setInputState : input is an invalid index");
//    }
}


Signal::SignalState AbstractGate::getOutputState() const
{
//    return mOutput->getState();
}


void AbstractGate::connect(AbstractGate * const otherGate,
                           const unsigned int otherInputIndex)
{
//    if(!otherGate)
//    {
//        throw invalid_argument("AbstractGate::connect : otherGate is null");
//    }

//    try
//    {
//        mOutput->connect(otherGate->mInputs.at(otherInputIndex));
//    }
//    catch(out_of_range)
//    {
//        throw invalid_argument("AbstractGate::connect : otherInputIndex invalid, no such input");
//    }
}


void AbstractGate::disConnect(AbstractGate * const otherGate,
                              const unsigned int otherInputIndex)
{
//    if(!otherGate)
//    {
//        throw invalid_argument("AbstractGate::disConnect : otherGate is null");
//    }

//    try
//    {
//        mOutput->disconnect(otherGate->mInputs.at(otherInputIndex));
//    }
//    catch(out_of_range)
//    {
//        throw invalid_argument("AbstractGate::disConnect : otherInputIndex invalid, no such input");
//    }
}


void AbstractGate::evaluate()
{
//    mGateState = evaluateState();
//    mOutput->setState(mGateState);
}


std::string AbstractGate::toString(void) const
{
//    if(mName.empty())
//    {
//        return "";
//    }

//    string retStr = "=== " + mName + " ===\n";

//    for(unsigned int index = 0; index < mInputs.size(); index++)
//    {
//        retStr += "Input[" + to_string(index) + "] : ";
//        retStr += (mInputs.at(index)->getState() == Signal::HIGH) ? "HIGH" : "LOW";
//        retStr += "\n";
//    }

//    retStr += "Output : ";
//    retStr += (mGateState == Signal::HIGH) ? "HIGH" : "LOW";

//    return retStr;
}





