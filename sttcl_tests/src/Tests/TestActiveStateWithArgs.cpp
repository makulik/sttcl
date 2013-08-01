/*
 * TestActiveStateWithArgs.cpp
 *
 *  Created on: May 21, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TestStateMachineMocks.h"
#include "TestActiveStateMocks.h"
#include "TestStateMocks.h"
#include "SttclTestActions.h"
#include "SttclTestAsyncActions.h"

class TestActiveStateWithArgs
: public ::testing::Test
{
public:
    TestActiveStateWithArgs()
    {
    }

    ~TestActiveStateWithArgs()
    {
    }
};

TEST_F(TestActiveStateWithArgs,Constructor)
{
    ::testing::NiceMock
        < TestActiveStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state;
}

TEST_F(TestActiveStateWithArgs,BasicStateInteractions1)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestActiveStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state;

    stateMachine.autoFinalize(false);
    stateMachine.initialState(&state);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(state,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,initSubStateMachinesImpl(false))
        .Times(1);
    EXPECT_CALL(state,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,exitImpl(&stateMachine))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    stateMachine.finalize(false);
}

TEST_F(TestActiveStateWithArgs,BasicStateInteractions2)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestActiveStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state;

    stateMachine.autoFinalize(false);
    stateMachine.initialState(&state);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(state,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,initSubStateMachinesImpl(false))
        .Times(1);
    EXPECT_CALL(state,finalizeSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(state,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,exitImpl(&stateMachine))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    stateMachine.finalize(true);
}

TEST_F(TestActiveStateWithArgs,BasicStateInteractions3)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestActiveStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state;

    stateMachine.autoFinalize(false);
    stateMachine.initialState(&state);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(state,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,initSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(state,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,exitImpl(&stateMachine))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    stateMachine.finalize(false);
}

TEST_F(TestActiveStateWithArgs,BasicStateInteractions4)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestActiveStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state;

    stateMachine.autoFinalize(false);
    stateMachine.initialState(&state);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(state,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,initSubStateMachinesImpl(_))
        .Times(1);
    EXPECT_CALL(state,finalizeSubStateMachinesImpl(_))
        .Times(1);
    EXPECT_CALL(state,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,exitImpl(&stateMachine))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    stateMachine.finalize(true);
}

TEST_F(TestActiveStateWithArgs,DirectTransition1)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestActiveStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state1(false,sttcl::TimeDuration<>(0,0,0,100),"state1");
    ::testing::NiceMock
        < TestSimpleStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state2("state2");

    stateMachine.autoFinalize(false);
    stateMachine.initialState(&state1);
    state1.setDirectTransitState(&state2);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(state1,checkDirectTransitionImpl(_,_,_))
        .Times(AtLeast(1));
    EXPECT_CALL(state1,exitingDoActionImpl())
        .Times(1);

    EXPECT_CALL(state2,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2,startDoImpl(&stateMachine))
        .Times(1);
// Direct transition prevents initializing sub state machines
//    EXPECT_CALL(state2,initSubStateMachinesImpl(_))
//        .Times(1);
    EXPECT_CALL(state2,finalizeSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(state2,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2,exitImpl(&stateMachine))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
//    stateMachine.enableLogging(true);
//    state1.enableLogging(true);
//    state2.enableLogging(true);

    stateMachine.initialize(true);
    EXPECT_TRUE(state1.waitForDoActionExited(sttcl::TimeDuration<>(0,0,0,100),5));
    stateMachine.finalize(true);
}

TEST_F(TestActiveStateWithArgs,DirectTransition2)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestActiveStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state(false,sttcl::TimeDuration<>(0,0,0,100),"state1");

    stateMachine.autoFinalize(false);
    stateMachine.initialState(&state);
    state.finalizeOnNextDirectTransit(true);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(state,checkDirectTransitionImpl(_,_,_))
        .Times(AtLeast(1));
    EXPECT_CALL(state,endDoImpl(_))
        .Times(1);
    EXPECT_CALL(stateMachine,finalizeImpl(_))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
//    stateMachine.enableLogging(true);
//    state.enableLogging(true);

    stateMachine.initialize(false);
    EXPECT_TRUE(state.waitForDoActionExited(sttcl::TimeDuration<>(0,0,0,100),5));
    stateMachine.finalize(true);
}
