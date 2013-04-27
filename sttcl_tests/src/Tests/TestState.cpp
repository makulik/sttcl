/*
 * TestState.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>

#include "SttclStateMachineMock.h"
#include "TestStateInterfaceMock.h"

class TestState : public ::testing::Test
{
public:
	TestState()
	{
	}

	~TestState()
	{
	}

private:
};

TEST_F(TestState,Constructor)
{
	::testing::NiceMock<TestStateInterfaceMock> state;
}

TEST_F(TestState,LifeCycle)
{
	::testing::NiceMock<TestStateInterfaceMock> state;
	::testing::NiceMock<SttclStateMachineMock> stateMachine;

	EXPECT_CALL(state, entryImpl(&stateMachine))
	    .Times(1);
	EXPECT_CALL(state, startDoImpl(&stateMachine))
	    .Times(1);
	EXPECT_CALL(state, endDoImpl(&stateMachine))
	    .Times(1);
	EXPECT_CALL(state, exitImpl(&stateMachine))
	    .Times(1);

	stateMachine.setInitialState(&state);
	stateMachine.initialize();
	stateMachine.finalize();
}

TEST_F(TestState,DirectTransition)
{
	::testing::NiceMock<TestStateInterfaceMock> state1("state1");
	::testing::NiceMock<TestStateInterfaceMock> state2("state2");
	::testing::NiceMock<SttclStateMachineMock> stateMachine;

	EXPECT_CALL(state1, entryImpl(&stateMachine))
	    .Times(1);
	EXPECT_CALL(state1, startDoImpl(&stateMachine))
	    .Times(1);
	EXPECT_CALL(state1, endDoImpl(&stateMachine))
	    .Times(1);
	EXPECT_CALL(state1, exitImpl(&stateMachine))
	    .Times(1);

	EXPECT_CALL(state2, entryImpl(&stateMachine))
	    .Times(1);
	EXPECT_CALL(state2, startDoImpl(&stateMachine))
	    .Times(1);
	EXPECT_CALL(state2, endDoImpl(&stateMachine))
	    .Times(1);
	EXPECT_CALL(state2, exitImpl(&stateMachine))
	    .Times(1);

//	stateMachine.enableLogs(true);
//	state1.enableLogs(true);
//	state2.enableLogs(true);

	stateMachine.setInitialState(&state1);
	state1.setDirectTransitState(&state2);

	stateMachine.initialize();
	stateMachine.finalize();
}
