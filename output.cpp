#include "output.h"

#include <stdexcept>
#include <set>
#include "abstractgate.h"
#include "input.h"

using namespace std;


Output::Output(void)
    : mParentGate(nullptr),
      mOutputState(Signal::LOW),
      mConnectedInputs({})
{ }


Output::Output(AbstractGate * const parentGate)
    : mParentGate(parentGate),
      mOutputState(Signal::LOW),
      mConnectedInputs({})
{
    if(!mParentGate)
    {
        throw std::invalid_argument("Output::Output : parentGate is null");
    }
}

Output::~Output()
{


    mOutputState = Signal::LOW;
    emitOutputSignal(Signal::LOW);

    for(Input * input : mConnectedInputs)
    {
        input->disconnect(this);
    }
}


void Output::setState(const Signal::SignalState newState)
{
    if(mOutputState != newState)
    {
        mOutputState = newState;
        emitOutputSignal(mOutputState);
    }
}


Signal::SignalState Output::getState(void) const
{
    return mOutputState;
}




void Output::emitOutputSignal(const Signal::SignalState signalState) const
{
    for(Input * input : mConnectedInputs)
    {
        input->setState(mOutputState);
    }
}

void Output::connect(Input * const input)
{
    if(!input)
    {
        throw invalid_argument("Output::connect : input is null");
    }

    mConnectedInputs.insert(input);
    input->connect(this);

    emitOutputSignal(mOutputState);
}

void Output::disconnect(Input * const input)
{
    if(!input)
    {
        throw invalid_argument("Output::disconnect : input is null");
    }

    if(mConnectedInputs.find(input) == mConnectedInputs.end())
    {
        throw invalid_argument("Output::disconnect : not connected to input");
    }
    else
    {
        mConnectedInputs.erase(input);

        input->disconnect(this); // todo : erlaubt bei zerstörung eines inputs ?
        input->setState(Signal::LOW); // todo : erlaubt bei zerstörung eines inputs ?
    }
}
