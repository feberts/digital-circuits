#include "abstractgate.h"

#include <stdexcept>

using namespace std;

const unsigned int MIN_INPUTS = 2;


AbstractGate::AbstractGate(const string & name)
    : AbstractGate(MIN_INPUTS, name)
{ }


AbstractGate::AbstractGate(const unsigned int numberOfInputs,
                           const string & name)
    : AbstractIOComponent(numberOfInputs, name)
{
    if(numberOfInputs < MIN_INPUTS)
    {
        throw invalid_argument("AbstractGate::AbstractGate : numberOfInputs must be > "
                               + to_string(MIN_INPUTS));
    }
}
