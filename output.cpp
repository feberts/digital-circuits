#include "output.h"

#include <stdexcept>
#include "input.h"

using namespace std;


Output::Output(void)
    : mState(Signal::LOW),
      mConnectedInputs({})
{ }


Output::~Output()
{
    mState = Signal::LOW;
    emitSignal();

    for(Input * const input : mConnectedInputs)
    {
        input->disconnect(this);
    }
}


void Output::setState(const Signal::SignalState newState)
{
    if(mState != newState)
    {
        mState = newState;
        emitSignal();
    }
}


void Output::connect(Input * const input)
{
    if(!input)
    {
        throw invalid_argument("Output::connect : input is null");
    }

    if(mConnectedInputs.find(input) != mConnectedInputs.end())
    {
        throw invalid_argument("Output::connect : already connected to input");
    }

    mConnectedInputs.insert(input);
    input->connect(this);

    emitSignal();
}


void Output::disconnect(Input * const input)
{
    disconnectCheck(input);
    mConnectedInputs.erase(input);

    input->disconnect(this);
    input->updateState();
}


void Output::disconnectFromDeletedInput(Input * const input)
{
    disconnectCheck(input);
    mConnectedInputs.erase(input);
}


void Output::disconnectCheck(Input * const input) const
{
    if(!input)
    {
        throw invalid_argument("Output::disconnectCheck : input is null");
    }

    if(mConnectedInputs.find(input) == mConnectedInputs.end())
    {
        throw invalid_argument("Output::disconnectCheck : not connected to input");
    }
}


Signal::SignalState Output::getState(void) const
{
    return mState;
}


void Output::emitSignal(void) const
{
    for(Input * const input : mConnectedInputs)
    {
        input->updateState();
    }
}
