/*
 * TestSimpleStateNoArgs.cpp
 *
 *  Created on: May 21, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TestStateMachineMocks.h"
#include "TestStateMocks.h"
#include "SttclTestActions.h"

class TestSimpleStateNoArgs
: public ::testing::Test
{
public:
    TestSimpleStateNoArgs()
    {
    }

    ~TestSimpleStateNoArgs()
    {
    }
};

TEST_F(TestSimpleStateNoArgs,Constructor)
{
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > state;
}

TEST_F(TestSimpleStateNoArgs,BasicStateInteractions1)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
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

TEST_F(TestSimpleStateNoArgs,BasicStateInteractions2)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
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

TEST_F(TestSimpleStateNoArgs,BasicStateInteractions3)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
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

TEST_F(TestSimpleStateNoArgs,BasicStateInteractions4)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
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

TEST_F(TestSimpleStateNoArgs,DirectTransition1)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > state1;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
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

TEST_F(TestSimpleStateNoArgs,DirectTransition2)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
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
