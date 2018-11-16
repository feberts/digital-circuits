#include "input.h"

#include <stdexcept>
#include "abstractgate.h"
#include "output.h"

using namespace std;


Input::Input(void)
    : mParentGate(nullptr),
      mInputState(Signal::LOW),
      mConnectedOutputs({})
{ }


Input::Input(AbstractGate * const parentGate)
    : mParentGate(parentGate),
      mInputState(Signal::LOW),
      mConnectedOutputs({})
{
    if(!mParentGate)
    {
        throw std::invalid_argument("Input::Input : parentGate is null");
    }
}

Input::~Input()
{
    for(Output * output : mConnectedOutputs)
    {
        output->disconnect(this);
    }
}


void Input::setState(const Signal::SignalState newState)
{
    if(mInputState != newState)
    {
        Signal::SignalState tempState = Signal::LOW;

        for(Output * output : mConnectedOutputs)
        {
            if(output->getState() == Signal::HIGH)
            {
                tempState = Signal::HIGH;
            }
        }

        if(mInputState != tempState)
        {
            mInputState = tempState;

            if(mParentGate)
            {
                mParentGate->evaluate();
            }
        }
    }
}


//void Input::setState(const Signal::SignalState newState)
//{
//    if(mInputState != newState)
//    {
//        mInputState = Signal::LOW;

//        for(Output * output : mConnectedOutputs)
//        {
//            if(output->getState() == Signal::HIGH)
//            {
//                mInputState = Signal::HIGH;
//            }
//        }

//            mParentGate->evaluate();

//    }
//}


Signal::SignalState Input::getState(void) const
{
    return mInputState;
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
