//Requirements
// Explicit transition table
// States could have multiple events
// States could have multiple routes to another states
// Event search should be optimized
// States business logic should be implemented as function pointers
// Each state must be attached to only one function

#pragma once

#include <map>
#include <memory>

class IFSM
{
};

typedef void (*StateHandler)();

template <class T>
struct State_t
{
    T state;
    StateHandler handler;
};

template <class State, class Event>
struct TransitionTable_t
{
    State_t<State> currentState;
    State_t<State> nextState;
    Event event;
};

template <class State, class Event>
class FSM
{
public:
    FSM(TransitionTable_t<State, Event> transitions_, bool continousRun_ = false);
    virtual ~FSM() = default;

    State GetState();
    void Run();

private:
    TransitionTable_t<State, Event> transitions;
    State_t<State> currentState;
    bool continousRun;
};

