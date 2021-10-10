//Requirements
// Explicit transition table
// States could have multiple events
// States could have multiple routes to another states
// Event search should be optimized
// States business logic should be implemented as function pointers
// Each state must be attached to only one function

#pragma once
#include <functional>
#include <iostream>
#include <map>

template <class State, class Event>
class FSM
{
    using TransitionsMap = std::map<std::pair<State, Event>, State>;
    using StatesHandlersMap = std::map<State, std::function<Event()>>;

public:
    FSM(const TransitionsMap transitions_, const StatesHandlersMap statesHandlers_, bool continousRun_ = false);
    virtual ~FSM() = default;

    State getState();
    void run();

private:
    State processStateTransition(Event event);
    Event executeStateHandler();

private:
    TransitionsMap transitions;
    StatesHandlersMap statesHandlers;
    bool continousRun;
    State currentState;
};

template <class State, class Event>
FSM<State, Event>::FSM(const TransitionsMap transitions_, const StatesHandlersMap statesHandlers_, bool continousRun_)
    : transitions(transitions_)
    , statesHandlers(statesHandlers_)
    , continousRun(continousRun_)
{
    currentState = State();
}

template <class State, class Event>
State FSM<State, Event>::getState()
{
    return currentState;
}

template <class State, class Event>
State FSM<State, Event>::processStateTransition(Event event)
{
    auto it = transitions.find(std::make_pair(currentState, event));
    if (it != transitions.end()) {
        return it->second;
    }

    return currentState;
}

template <class State, class Event>
Event FSM<State, Event>::executeStateHandler()
{
    return statesHandlers[currentState]();
}

template <class State, class Event>
void FSM<State, Event>::run()
{
    do
    {
        Event newEvent = executeStateHandler();
        currentState = processStateTransition(newEvent);

    } while (continousRun);
}