/*
 * TestStateMachineWithArgs.cpp
 *
 *  Created on: May 21, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TestStateMachineMocks.h"
#include "TestStateMocks.h"
#include "SttclTestActions.h"

class TestStateMachineWithArgs
: public ::testing::Test
{
public:
    TestStateMachineWithArgs()
    {
    }

    ~TestStateMachineWithArgs()
    {
    }
};

TEST_F(TestStateMachineWithArgs,Constructor)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
}

TEST_F(TestStateMachineWithArgs,Initialize1)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
//    stateMachine.enableLogging(true);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(stateMachine,initializeImpl(false))
        .Times(1);
    EXPECT_CALL(stateMachine,getInitialStateImpl())
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
}

TEST_F(TestStateMachineWithArgs,Initialize2)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(stateMachine,initializeImpl(true))
        .Times(1);
    EXPECT_CALL(stateMachine,getInitialStateImpl())
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
}

TEST_F(TestStateMachineWithArgs,Finalize1)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    stateMachine.autoFinalize(false);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(stateMachine,finalizeImpl(true))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    stateMachine.finalize();
}

TEST_F(TestStateMachineWithArgs,Finalize2)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    stateMachine.autoFinalize(false);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(stateMachine,finalizeImpl(false))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    stateMachine.finalize(false);
}

TEST_F(TestStateMachineWithArgs,EventPropagation)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state;

    stateMachine.autoFinalize(false);
    stateMachine.initialState(&state);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(state,handleEvent1(&stateMachine,"Hello!",42))
        .Times(1);
    EXPECT_CALL(state,handleEvent2(&stateMachine,3.1415))
        .Times(1);
    EXPECT_CALL(state,handleEvent3(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,handleEvent4(&stateMachine,12345))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    stateMachine.triggerEvent1("Hello!",42);
    stateMachine.triggerEvent2(3.1415);
    stateMachine.triggerEvent3();
    stateMachine.triggerEvent4(12345);
    stateMachine.finalize(false);
}

TEST_F(TestStateMachineWithArgs,ChangeState)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state1;
    ::testing::NiceMock
        < TestSimpleStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state2;

    stateMachine.autoFinalize(false);
    stateMachine.initialState(&state1);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(state1,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state1,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state1,handleEvent1(&stateMachine,"Hello!",42))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(TestSimpleStateWithArgsMock<TestStateMachineWithEventArgsMock>, handleEvent1, &state1, &state2) );
    EXPECT_CALL(state1,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state1,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(state2,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2,handleEvent2(&stateMachine,3.1415))
        .Times(1);
    EXPECT_CALL(state2,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2,exitImpl(&stateMachine))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    stateMachine.triggerEvent1("Hello!",42);
    stateMachine.triggerEvent2(3.1415);
    stateMachine.finalize(false);
}
