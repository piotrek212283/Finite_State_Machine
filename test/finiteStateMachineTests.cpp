#include "finiteStateMachine.h"
#include "gtest/gtest.h"
#include <map>
#include <memory>
#include <vector>
#include <iostream>

enum class Event
{
    Transition_To_S1,
    Transition_To_S2,
    Transition_To_S3,
    Transition_To_S4
};

enum class State
{
    S1,
    S2,
    S3,
    S4
};

Event s1_handler()
{
    std::cout << "S1 Handler" << std::endl;
    return Event::Transition_To_S2;
}

Event s2_handler()
{
    std::cout << "S2 Handler" << std::endl;
    return Event::Transition_To_S3;
}

Event s3_handler()
{
    std::cout << "S3 Handler" << std::endl;
    return Event::Transition_To_S4;
}

Event s4_handler()
{
    std::cout << "S4 Handler" << std::endl;
    return Event::Transition_To_S1;
}

std::map<State, std::function<Event()>> stateHandlers =
    {
        {State::S1, std::bind(s1_handler)},
        {State::S2, std::bind(s2_handler)},
        {State::S3, std::bind(s3_handler)},
        {State::S4, std::bind(s4_handler)}};

std::vector<Transition_t<State, Event>> transitionTable =
    {
        {State::S1, Event::Transition_To_S2, State::S2},
        {State::S2, Event::Transition_To_S3, State::S3},
        {State::S3, Event::Transition_To_S4, State::S4},
        {State::S4, Event::Transition_To_S1, State::S1}};

class FSM_Tests : public ::testing::Test
{
public:
    FSM_Tests()
    {
    }

    void SetUp()
    {
        finiteStateMachine = std::make_shared<FSM<State, Event>>(transitionTable, stateHandlers, false);
    }

public:
    std::shared_ptr<FSM<State, Event>> finiteStateMachine;
};


TEST_F(FSM_Tests, FSM_Should_Init_In_First_State)
{
    EXPECT_EQ(finiteStateMachine->GetState(), State::S1);
}

TEST_F(FSM_Tests, FSM_Should_Change_State_When_Event_Occured)
{
    EXPECT_EQ(finiteStateMachine->GetState(), State::S1);
    finiteStateMachine->Run();
    EXPECT_EQ(finiteStateMachine->GetState(), State::S2);
}

