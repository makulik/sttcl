/*
 * TestSimpleStateWithArgs.cpp
 *
 *  Created on: May 21, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TestStateMachineMocks.h"
#include "TestStateMocks.h"
#include "SttclTestActions.h"

class TestSimpleStateWithArgs
: public ::testing::Test
{
public:
    TestSimpleStateWithArgs()
    {
    }

    ~TestSimpleStateWithArgs()
    {
    }
};

TEST_F(TestSimpleStateWithArgs,Constructor)
{
    ::testing::NiceMock
        < TestSimpleStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state;
}

TEST_F(TestSimpleStateWithArgs,BasicStateInteractions1)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateWithArgsMock<TestStateMachineWithEventArgsMock>
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

TEST_F(TestSimpleStateWithArgs,BasicStateInteractions2)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateWithArgsMock<TestStateMachineWithEventArgsMock>
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

TEST_F(TestSimpleStateWithArgs,BasicStateInteractions3)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateWithArgsMock<TestStateMachineWithEventArgsMock>
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

TEST_F(TestSimpleStateWithArgs,BasicStateInteractions4)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateWithArgsMock<TestStateMachineWithEventArgsMock>
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
    EXPECT_CALL(state,finalizeSubStateMachinesImpl(true))
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

TEST_F(TestSimpleStateWithArgs,DirectTransition1)
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
    state1.setDirectTransitState(&state2);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(state1,checkDirectTransitionImpl(_,_,_))
        .Times(1);

    EXPECT_CALL(state2,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2,initSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(state2,finalizeSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(state2,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2,exitImpl(&stateMachine))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    stateMachine.finalize(true);
}

TEST_F(TestSimpleStateWithArgs,DirectTransition2)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > state;

    stateMachine.autoFinalize(false);
    stateMachine.initialState(&state);
    state.finalizeOnNextDirectTransit();

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(state,checkDirectTransitionImpl(_,_,_))
        .Times(1);
    EXPECT_CALL(stateMachine,finalizeImpl(_))
        .Times(2);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    stateMachine.finalize(true);
}
