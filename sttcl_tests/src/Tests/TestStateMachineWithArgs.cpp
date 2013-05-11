/*
 * TestStateMachineWithArgs.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>

#include "SttclStateMachineWithArgsMock.h"
#include "TestStateInterfaceWithArgsMock.h"

class TestStateMachineWithArgs : public ::testing::Test
{
public:
	TestStateMachineWithArgs()
	{
	}

	~TestStateMachineWithArgs()
	{
	}

protected:
};

TEST_F(TestStateMachineWithArgs,Constructor)
{
	::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;
}

TEST_F(TestStateMachineWithArgs,Initialize1)
{
	::testing::NiceMock<TestStateInterfaceWithArgsMock> state1;
	::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;

	EXPECT_CALL(stateMachine, initializeImpl(false))
	    .Times(1);
	EXPECT_CALL(stateMachine, getInitialStateImpl())
	    .Times(1);
	EXPECT_CALL(state1, entryImpl(_))
	    .Times(1);
	EXPECT_CALL(stateMachine, isReadyImpl())
	    .Times(1);

	stateMachine.setInitialState(&state1);
	stateMachine.initialize();
	stateMachine.finalize();
}

TEST_F(TestStateMachineWithArgs,Initialize2)
{
	::testing::NiceMock<TestStateInterfaceWithArgsMock> state1;
	::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;

	EXPECT_CALL(stateMachine, initializeImpl(true))
	    .Times(1);
	EXPECT_CALL(stateMachine, getInitialStateImpl())
	    .Times(1);
	EXPECT_CALL(state1, entryImpl(_))
	    .Times(1);
	EXPECT_CALL(stateMachine, isReadyImpl())
	    .Times(1);
	EXPECT_CALL(stateMachine, finalizeImpl(true))
	    .Times(2);

	stateMachine.setInitialState(&state1);
	stateMachine.initialize(true);
	stateMachine.finalize();
}

TEST_F(TestStateMachineWithArgs,Finalize)
{
	::testing::NiceMock<TestStateInterfaceWithArgsMock> state1;
	::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;

	EXPECT_CALL(stateMachine, initializeImpl(false))
	    .Times(1);
	EXPECT_CALL(stateMachine, getInitialStateImpl())
	    .Times(1);
	EXPECT_CALL(state1, entryImpl(_))
	    .Times(1);
	EXPECT_CALL(stateMachine, isReadyImpl())
	    .Times(1);
	EXPECT_CALL(stateMachine, finalizeImpl(true))
	    .Times(1);
	EXPECT_CALL(state1, exitImpl(_))
	    .Times(1);

	stateMachine.setInitialState(&state1);
	stateMachine.initialize();
	stateMachine.finalize();
}

TEST_F(TestStateMachineWithArgs,EventPropagation)
{
    ::testing::NiceMock<TestStateInterfaceWithArgsMock> state1;
    ::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;

    EXPECT_CALL(stateMachine, initializeImpl(false))
        .Times(1);
    EXPECT_CALL(stateMachine, getInitialStateImpl())
        .Times(1);
    EXPECT_CALL(state1, entryImpl(_))
        .Times(1);
    EXPECT_CALL(stateMachine, isReadyImpl())
        .Times(1);
    EXPECT_CALL(state1, handleEvent1(_,42,"Hello!"))
        .Times(1);
    EXPECT_CALL(state1, handleEvent2(_,3.1415))
        .Times(1);
    EXPECT_CALL(state1, handleEvent3(_))
        .Times(1);
    EXPECT_CALL(state1, handleEvent4(_,4679))
        .Times(1);
    EXPECT_CALL(stateMachine, finalizeImpl(true))
        .Times(1);
    EXPECT_CALL(state1, exitImpl(_))
        .Times(1);

    stateMachine.setInitialState(&state1);
    stateMachine.initialize();
    stateMachine.triggerEvent1(42,"Hello!");
    stateMachine.triggerEvent2(3.1415);
    stateMachine.triggerEvent3();
    stateMachine.triggerEvent4(4679);
    stateMachine.finalize();
}
