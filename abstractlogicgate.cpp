#include "abstractlogicgate.h"

#include <stdexcept>

using namespace std;

typedef pair<AbstractLogicGate *, set<unsigned int>> pairGateInputset;


AbstractLogicGate::AbstractLogicGate(const string & name)
    : AbstractLogicGate(2, name)
{ }


AbstractLogicGate::AbstractLogicGate(const unsigned int numberOfInputs,
                                     const string & name)
    : AbstractComponent(name),
      mInputs(vector<DigitalInput>(numberOfInputs, DigitalInput(this))),
      mConnectedInputs({}),
      mConnectedOutputs({}),
      mOutputState(Signal::LOW)
{
    if(numberOfInputs < 2)
    {
        throw invalid_argument("AbstractLogicGate::AbstractLogicGate : numberOfInputs must be > 1");
    }
}


AbstractLogicGate::~AbstractLogicGate(void)
{
    emitOutputSignal(Signal::LOW);

    for(auto gate = mConnectedOutputs.begin(); gate != mConnectedOutputs.end(); gate++)
    {
        (*gate)->disConnectInput(this);
    }
}


void AbstractLogicGate::setInputState(const unsigned int inputIndex, const Signal::SignalState newState)
{
    try
    {
        mInputs.at(inputIndex).setState(newState);
    }
    catch(out_of_range)
    {
        throw invalid_argument("AbstractLogicGate::setInput : input is an invalid index");
    }
}


Signal::SignalState AbstractLogicGate::getOutputState() const
{
    return mOutputState;
}


void AbstractLogicGate::connect(AbstractLogicGate * const otherGate,
                                const unsigned int otherInputIndex)
{
    checkConnection(otherGate, otherInputIndex);

    auto gate = mConnectedInputs.find(otherGate);

    if(gate == mConnectedInputs.end()) // not yet connected to otherGate
    {
        set<unsigned int> inputSet;
        inputSet.insert(otherInputIndex);

        mConnectedInputs.insert(pairGateInputset(otherGate, inputSet));
    }
    else // already connected to at least one input of otherGate
    {
        gate->second.insert(otherInputIndex);
    }

    evaluate(); // todo nötig ?

    otherGate->connectOutput(this);
}


void AbstractLogicGate::disConnect(AbstractLogicGate * const otherGate,
                                   const unsigned int otherInputIndex)
{
    checkConnection(otherGate, otherInputIndex);

    auto gate = mConnectedInputs.find(otherGate);

    if(gate == mConnectedInputs.end()) // no connections to otherGate found
    {
        throw invalid_argument("AbstractLogicGate::disConnect : not connected to otherGate");
    }
    else // connected to at least one input of otherGate
    {
        auto input = gate->second.find(otherInputIndex);

        if(input == gate->second.end()) // not connected to this specific input
        {
            throw invalid_argument("AbstractLogicGate::disConnect : not connected to this specific input");
        }
        else // connected to this specific input
        {
            otherGate->setInputState(otherInputIndex, Signal::LOW);

            gate->second.erase(otherInputIndex);

            if(gate->second.empty()) // remove otherGate completely if all inputs disconnected
            {
                mConnectedInputs.erase(otherGate);
            }
        }
    }
}


unsigned int AbstractLogicGate::getNumberOfInputs(void) const
{
    return mInputs.size();
}


void AbstractLogicGate::evaluate()
{
    mOutputState = evaluateOutput();
    emitOutputSignal(mOutputState);
}


std::string AbstractLogicGate::toString(void) const
{
    if(mName.empty())
    {
        return "";
    }

    string retStr = "=== " + mName + " ===\n";

    for(unsigned int index = 0; index < mInputs.size(); index++)
    {
        retStr += "Input[" + to_string(index) + "] : ";
        retStr += (mInputs.at(index).getState() == Signal::HIGH) ? "HIGH" : "LOW";
        retStr += "\n";
    }

    retStr += "Output : ";
    retStr += (mOutputState == Signal::HIGH) ? "HIGH" : "LOW";

    for (auto gate = mConnectedInputs.cbegin(); gate != mConnectedInputs.cend(); ++gate)
    {
        retStr += "\nConnected to : " + gate->first->getName() + "[";

        for (auto input = gate->second.cbegin(); input != gate->second.cend(); ++input)
        {
            retStr += to_string(*input) + ", ";
        }

        retStr.pop_back();
        retStr.pop_back();
        retStr += "]";
    }

    return retStr;
}


void AbstractLogicGate::emitOutputSignal(const Signal::SignalState signalState) const
{
    for(auto gate = mConnectedInputs.cbegin(); gate != mConnectedInputs.cend(); ++gate)
    {
        for(auto input = gate->second.cbegin(); input != gate->second.cend(); ++input)
        {
            gate->first->setInputState(*input, signalState);
        }
    }
}


void AbstractLogicGate::checkConnection(AbstractLogicGate * const otherGate,
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


void AbstractLogicGate::connectOutput(AbstractLogicGate * const otherGate)
{
    mConnectedOutputs.insert(otherGate);
}


void AbstractLogicGate::disConnectInput(AbstractLogicGate * const otherGate)
{
    mConnectedInputs.erase(otherGate);
}
