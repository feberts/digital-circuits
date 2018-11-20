#include "abstractcomponent.h"

using namespace std;


AbstractComponent::AbstractComponent(const string & name)
    : mName(name)
{ }


std::string AbstractComponent::getName(void) const
{
    return mName;
}
