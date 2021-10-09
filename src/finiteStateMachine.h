//Requirements
// Explicit transition table
// States could have multiple events
// States could have multiple routes to another states
// Event search should be optimized
// States business logic should be implemented as function pointers
// Each state must be attached to only one function

#pragma once
#include <functional>


template <class State, class Event>
struct State_t
{
    State state;
    std::function<Event()> handler;
};

template <class State, class Event>
struct Transition_t
{
    State_t<State, Event> currentState;
    State_t<State, Event> nextState;
    Event event;
};

template <class State, class Event>
class FSM
{
public:
    FSM(std::vector<Transition_t<State, Event>> transitionsTable_, bool continousRun_ = false);
    virtual ~FSM() = default;

    State GetState();
    void Run();

private:
    std::vector<Transition_t<State, Event>> transitionsTable;
    State_t<State, Event> currentState;
    bool continousRun;
};

