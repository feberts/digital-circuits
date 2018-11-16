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
      mOutput(new Output(this)),
      mGateState(Signal::LOW)
{
    if(numberOfInputs < 2)
    {
        throw invalid_argument("AbstractLogicGate::AbstractLogicGate : numberOfInputs must be > 1");
    }

    for(unsigned int index = 0; index < numberOfInputs; index++)
    {
        mInputs.push_back(new Input(this, index));
    }
}


AbstractGate::~AbstractGate(void)
{
    for(Input * input : mInputs)
    {
        delete input;
    }

    delete mOutput;
}


void AbstractGate::setInputState(const unsigned int inputIndex, const Signal::SignalState newState)
{
    try
    {
        mInputs.at(inputIndex)->setState(newState);
    }
    catch(out_of_range)
    {
        throw invalid_argument("AbstractLogicGate::setInput : input is an invalid index");
    }
}


Signal::SignalState AbstractGate::getOutputState() const
{
    return mOutput->getOutputState();
}


void AbstractGate::connect(AbstractGate * const otherGate,
                                const unsigned int otherInputIndex)
{
    checkConnection(otherGate, otherInputIndex);
    mOutput->connect(otherGate, otherInputIndex);
}


void AbstractGate::disConnect(AbstractGate * const otherGate,
                                   const unsigned int otherInputIndex)
{
    checkConnection(otherGate, otherInputIndex);
    mOutput->disConnect(otherGate, otherInputIndex);
}

void AbstractGate::disConnectFromDeletedGate(AbstractGate * const otherGate,
                                   const unsigned int otherInputIndex)
{
    checkConnection(otherGate, otherInputIndex);
    mOutput->disConnect(otherGate, otherInputIndex, true);
}

unsigned int AbstractGate::getNumberOfInputs(void) const
{
    return mInputs.size();
}


void AbstractGate::evaluate()
{
    mGateState = evaluateState();
    mOutput->setState(mGateState);
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
    //        retStr += (mInputs.at(index).getState() == Signal::HIGH) ? "HIGH" : "LOW";
    //        retStr += "\n";
    //    }

    //    retStr += "Output : ";
    //    retStr += (mGateState == Signal::HIGH) ? "HIGH" : "LOW";

    //    for (auto gate = mConnectionsToOtherGates.cbegin(); gate != mConnectionsToOtherGates.cend(); ++gate)
    //    {
    //        retStr += "\nOutput connected to : " + gate->first->getName() + "[";

    //        for (auto input = gate->second.cbegin(); input != gate->second.cend(); ++input)
    //        {
    //            retStr += to_string(*input) + ", ";
    //        }

    //        retStr.pop_back();
    //        retStr.pop_back();
    //        retStr += "]";
    //    }

    //    return retStr;
}



void AbstractGate::checkConnection(AbstractGate * const otherGate,
                                        const unsigned int otherInputIndex) const
{
    if(!otherGate)
    {
        throw invalid_argument("AbstractLogicGate::checkConnection : otherGate is null");
    }

    if(otherInputIndex >= otherGate->getNumberOfInputs())
    {
        throw invalid_argument("AbstractLogicGate::checkConnection : otherInputIndex invalid, no such input");
    }
}


void AbstractGate::connectToOutput(AbstractGate * const otherGate, const unsigned int inputIndex)
{
    if(!otherGate)
    {
        throw invalid_argument("AbstractLogicGate::connectToOutput : otherGate is null");
    }

    try
    {
        mInputs.at(inputIndex)->connectToOutput(otherGate);
    }
    catch(out_of_range)
    {
        throw invalid_argument("AbstractLogicGate::connectToOutput : inputIndex is an invalid index");
    }
}


void AbstractGate::disConnectFromOutput(AbstractGate * const otherGate, const unsigned int inputIndex)
{
    if(!otherGate)
    {
        throw invalid_argument("AbstractLogicGate::disConnect : otherGate is null");
    }

    try
    {
        mInputs.at(inputIndex)->disConnectFromOutput(otherGate);
    }
    catch(out_of_range)
    {
        throw invalid_argument("AbstractLogicGate::disConnectFromOutput : inputIndex is an invalid index");
    }
}
