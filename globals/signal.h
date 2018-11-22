#ifndef SIGNAL_H
#define SIGNAL_H

#define EVALUATE_IMMEDIATELY // call evaluate() automatically


namespace Signal
{
    typedef bool SignalState;

    extern const SignalState HIGH;
    extern const SignalState LOW;
    extern const SignalState ON;
    extern const SignalState OFF;
};

#endif // SIGNAL_H
