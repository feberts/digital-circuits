#include "abstractiocomponent.h"

using namespace std;


void AbstractIOComponent::evaluate(void)
{
    mState = evaluateState();
    mOutput->setState(mState);
}




