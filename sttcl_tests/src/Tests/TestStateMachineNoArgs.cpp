/*
 * TestStateMachineNoArgs.cpp
 *
 *  Created on: May 21, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TestStateMachineMocks.h"
#include "TestStateMocks.h"
#include "SttclTestActions.h"

class TestStateMachineNoArgs
: public ::testing::Test
{
public:
    TestStateMachineNoArgs()
    {
    }

    ~TestStateMachineNoArgs()
    {
    }
};

TEST_F(TestStateMachineNoArgs,Constructor)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
}

TEST_F(TestStateMachineNoArgs,Initialize1)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
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

TEST_F(TestStateMachineNoArgs,Initialize2)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;

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

TEST_F(TestStateMachineNoArgs,Finalize1)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
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

TEST_F(TestStateMachineNoArgs,Finalize2)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
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

TEST_F(TestStateMachineNoArgs,EventPropagation)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > state;

    stateMachine.autoFinalize(false);
    stateMachine.initialState(&state);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(state,handleEvent1(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,handleEvent2(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,handleEvent3(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,handleEvent4(&stateMachine))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    stateMachine.triggerEvent1();
    stateMachine.triggerEvent2();
    stateMachine.triggerEvent3();
    stateMachine.triggerEvent4();
    stateMachine.finalize(false);
}

TEST_F(TestStateMachineNoArgs,ChangeState)
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

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(state1,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state1,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state1,handleEvent1(&stateMachine))
        .Times(1)
        .WillOnce(DoStateChange(&state1,&state2));
    EXPECT_CALL(state1,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state1,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(state2,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2,handleEvent2(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2,exitImpl(&stateMachine))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    stateMachine.triggerEvent1();
    stateMachine.triggerEvent2();
    stateMachine.finalize(false);
}
