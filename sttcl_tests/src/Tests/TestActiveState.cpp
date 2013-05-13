/*
 * TestActiveState.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <unistd.h>

#include "SttclStateMachineMock.h"
#include "TestStateInterfaceMock.h"
#include "SttclActiveStateMock.h"
#include "SttclTestAsyncActions.h"
#include "SttclTestActions.h"

class TestActiveState : public ::testing::Test
{
public:
	TestActiveState()
	{
	}

	~TestActiveState()
	{
	}

private:
};

TEST_F(TestActiveState,Constructor)
{
	::testing::NiceMock<SttclActiveStateMock> state;
}

TEST_F(TestActiveState,LifeCycle)
{
	::testing::NiceMock<SttclActiveStateMock> state;
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

TEST_F(TestActiveState,DirectTransition)
{
	::testing::NiceMock<SttclActiveStateMock> state1("state1");
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
	EXPECT_CALL(state1, exitingDoActionImpl())
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
//	static_cast<SttclStateMachineMock::StateMachineBaseClass::StateBaseClass*>(&state1)->joinDoAction(&stateMachine);
    ASSERT_TRUE(state1.waitForDoActionExited(sttcl::TimeDuration<>(0,0,0,100),20));
//	sleep(2);
	stateMachine.finalize();
}

TEST_F(TestActiveState,ChangeState)
{
    ::testing::NiceMock<SttclActiveStateMock> state1("state1");
    ::testing::NiceMock<TestStateInterfaceMock> state2("state2");
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;

    EXPECT_CALL(state1, entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state1, startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state1, handleEvent1(&stateMachine))
        .Times(1)
        .WillOnce(DoStateChange(&state1,&state2));
    EXPECT_CALL(state1, endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state1, exitImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state1, exitingDoActionImpl())
        .Times(1);

    EXPECT_CALL(state2, entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2, startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2, endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state2, exitImpl(&stateMachine))
        .Times(1);

//  stateMachine.enableLogs(true);
//  state1.enableLogs(true);
//  state2.enableLogs(true);

    stateMachine.setInitialState(&state1);

    stateMachine.initialize();
    stateMachine.triggerEvent1();
    ASSERT_TRUE(state1.waitForDoActionExited(sttcl::TimeDuration<>(0,0,0,100),20));
    stateMachine.finalize();
}
