#include "finiteStateMachine.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iostream>
#include <map>
#include <memory>
#include <vector>

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

class IHandlers
{
public:
    IHandlers() = default;
    virtual ~IHandlers() = default;

    virtual Event s1_handler() = 0;
    virtual Event s2_handler() = 0;
    virtual Event s3_handler() = 0;
    virtual Event s4_handler() = 0;
};

class MockIHandlers : public IHandlers
{
public:
    MOCK_METHOD(Event, s1_handler, (), (override));
    MOCK_METHOD(Event, s2_handler, (), (override));
    MOCK_METHOD(Event, s3_handler, (), (override));
    MOCK_METHOD(Event, s4_handler, (), (override));
};

class FSM_Tests : public ::testing::Test
{
public:
    FSM_Tests()
    {
        statesHandlers = {
            {State::S1, std::bind(&MockIHandlers::s1_handler, &handlers)},
            {State::S2, std::bind(&MockIHandlers::s2_handler, &handlers)},
            {State::S3, std::bind(&MockIHandlers::s3_handler, &handlers)},
            {State::S4, std::bind(&MockIHandlers::s4_handler, &handlers)}};

        transitionTable = {
            {{State::S1, Event::Transition_To_S2}, State::S2},
            {{State::S1, Event::Transition_To_S1}, State::S1},
            {{State::S2, Event::Transition_To_S3}, State::S3},
            {{State::S3, Event::Transition_To_S4}, State::S4},
            {{State::S4, Event::Transition_To_S1}, State::S1}};
    }

    void SetUp()
    {
        finiteStateMachine = std::make_shared<FSM<State, Event>>(transitionTable, statesHandlers, false);
    }

public:
    MockIHandlers handlers;
    std::shared_ptr<FSM<State, Event>> finiteStateMachine;
    std::map<std::pair<State, Event>, State> transitionTable;
    std::map<State, std::function<Event()>> statesHandlers;
};

TEST_F(FSM_Tests, FSM_Should_Init_In_First_State)
{
    EXPECT_EQ(finiteStateMachine->getState(), State::S1);
}

TEST_F(FSM_Tests, FSM_Should_Change_State_When_Event_Occured)
{
    EXPECT_CALL(handlers, s1_handler())
        .WillOnce(testing::Return(Event::Transition_To_S2));

    finiteStateMachine->run();

    EXPECT_EQ(finiteStateMachine->getState(), State::S2);
}

TEST_F(FSM_Tests, FSM_Shoud_Handle_Multiple_Events_Attached_To_One_State)
{
    EXPECT_CALL(handlers, s1_handler())
        .WillOnce(testing::Return(Event::Transition_To_S1))
        .WillOnce(testing::Return(Event::Transition_To_S2));

    finiteStateMachine->run();
    auto firstState = finiteStateMachine->getState();

    finiteStateMachine->run();
    auto secondState = finiteStateMachine->getState();

    EXPECT_EQ(firstState, State::S1);
    EXPECT_EQ(secondState, State::S2);
}



