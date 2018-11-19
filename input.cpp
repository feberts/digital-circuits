#include "input.h"

#include <stdexcept>
#include "output.h"
#include "abstractinputcomponent.h"

using namespace std;


Input::Input(void)
    : mParentComponent(nullptr),
      mState(Signal::LOW),
      mConnectedOutputs({})
{ }


Input::Input(AbstractInputComponent * const parentComponent)
    : mParentComponent(parentComponent),
      mState(Signal::LOW),
      mConnectedOutputs({})
{
    if(!mParentComponent)
    {
        throw std::invalid_argument("Input::Input : parentComponent is null");
    }
}


Input::~Input()
{
    for(Output * const output : mConnectedOutputs)
    {
        output->disconnectFromDeletedInput(this);
    }
}


Signal::SignalState Input::getState(void) const
{
    return mState;
}


void Input::updateState(void)
{
    Signal::SignalState newState = Signal::LOW;

    for(Output const * const output : mConnectedOutputs)
    {
        if(output->getState() == Signal::HIGH)
        {
            newState = Signal::HIGH;
        }
    }

    if(mState != newState)
    {
        mState = newState;

        if(mParentComponent) // see Input::Input
        {
            mParentComponent->evaluate();
        }
    }
}


void Input::connect(Output * const output)
{
    if(!output)
    {
        throw invalid_argument("Input::connect : output is null");
    }

    mConnectedOutputs.insert(output);
}


void Input::disconnect(Output * const output)
{
    if(!output)
    {
        throw invalid_argument("Input::disconnect : output is null");
    }

    mConnectedOutputs.erase(output);
}


