//Requirements
// Explicit transition table
// States could have multiple events
// States could have multiple routes to another states
// Event search should be optimized
// States business logic should be implemented as function pointers
// Each state must be attached to only one function

#pragma once
#include <functional>
#include <map>
#include <iostream>

template <class State, class Event>
struct Transition_t
{
    State currentState;
    Event event;
    State nextState;
};

template <class State, class Event>
class FSM
{
public:
    FSM(const std::vector<Transition_t<State, Event>> transitionsTable_, const std::map<State, std::function<Event()>> stateHandlers_, bool continousRun_ = false);
    virtual ~FSM() = default;

    State GetState();
    void Run();

private:
    std::vector<Transition_t<State, Event>> transitionsTable;
    std::map<State, std::function<Event()>> stateHandlers;
    State currentState;
    bool continousRun;
};

template <class State, class Event>
FSM<State, Event>::FSM(const std::vector<Transition_t<State, Event>> transitionsTable_, const std::map<State, std::function<Event()>> stateHandlers_, bool continousRun_) : transitionsTable(transitionsTable_), stateHandlers(stateHandlers_), continousRun(continousRun_)
{
    currentState = transitionsTable.at(0).currentState;
}

template <class State, class Event>
State FSM<State, Event>::GetState()
{
    return currentState;
}

template <class State, class Event>
void FSM<State, Event>::Run()
{
    do
    {
        Event newEvent = stateHandlers[currentState]();

        //Search through vector table
        for (auto &transition : transitionsTable)
        {
            if (transition.event == newEvent) {
                if (transition.currentState == currentState)
                {
                    currentState = transition.nextState;
                }
            }
        }

    } while (continousRun);
    
}