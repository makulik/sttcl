/*
 * TestStateMachine.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>

#include "SttclStateMachineMock.h"
#include "TestStateInterfaceMock.h"

class TestStateMachine : public ::testing::Test
{
public:
	TestStateMachine()
	{
	}

	~TestStateMachine()
	{
	}

protected:
};

TEST_F(TestStateMachine,Constructor)
{
	::testing::NiceMock<SttclStateMachineMock> stateMachine;
}

TEST_F(TestStateMachine,Initialize1)
{
	::testing::NiceMock<TestStateInterfaceMock> state1;
	::testing::NiceMock<SttclStateMachineMock> stateMachine;

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

TEST_F(TestStateMachine,Initialize2)
{
	::testing::NiceMock<TestStateInterfaceMock> state1;
	::testing::NiceMock<SttclStateMachineMock> stateMachine;

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

TEST_F(TestStateMachine,Finalize)
{
	::testing::NiceMock<TestStateInterfaceMock> state1;
	::testing::NiceMock<SttclStateMachineMock> stateMachine;

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
