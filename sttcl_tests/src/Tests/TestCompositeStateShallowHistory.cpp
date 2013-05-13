/*
 * TestCompositeStateShallowHistory.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TestStateInterfaceMock.h"
#include "TestCompositeStateShallowHistoryMock.h"
#include "SttclStateMachineMock.h"
#include "TestInnerStateInterfaceShallowHistoryMock.h"
#include "SttclTestActions.h"

class TestCompositeStateShallowHistory : public ::testing::Test
{
public:
	TestCompositeStateShallowHistory()
	{
	}

	~TestCompositeStateShallowHistory()
	{
	}

private:
};

TEST_F(TestCompositeStateShallowHistory,Constructor)
{
    ::testing::NiceMock<TestCompositeStateShallowHistoryMock> compositeState;
}

TEST_F(TestCompositeStateShallowHistory,LifeCycle)
{
    ::testing::NiceMock<TestCompositeStateShallowHistoryMock> compositeState;
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;

    EXPECT_CALL(compositeState, entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, exitImpl(&stateMachine))
        .Times(1);

//    stateMachine.enableLogs(true);
//    compositeState.enableLogs(true);

    stateMachine.setInitialState(&compositeState);
    stateMachine.initialize();
    stateMachine.finalize();

}

TEST_F(TestCompositeStateShallowHistory,EventPropagation)
{
    ::testing::NiceMock<TestInnerStateInterfaceShallowHistoryMock> innerState("innerState");
    ::testing::NiceMock<TestCompositeStateShallowHistoryMock> compositeState("compositeState");
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;

    EXPECT_CALL(compositeState, entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, handleEvent1(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, handleEvent2(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, handleEvent3(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, handleEvent4(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState, entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState, startDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState, handleEvent1(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState, handleEvent2(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState, handleEvent3(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState, handleEvent4(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState, endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState, exitImpl(&compositeState))
        .Times(1);

//    stateMachine.enableLogs(true);
//    compositeState.enableLogs(true);
//    innerState.enableLogs(true);

    compositeState.setInitialState(&innerState);
    stateMachine.setInitialState(&compositeState);
    stateMachine.initialize();
    stateMachine.triggerEvent1();
    stateMachine.triggerEvent2();
    stateMachine.triggerEvent3();
    stateMachine.triggerEvent4();
    stateMachine.finalize();

}

TEST_F(TestCompositeStateShallowHistory,ChangeState)
{
    ::testing::NiceMock<TestCompositeStateShallowHistoryMock> compositeState;
    ::testing::NiceMock<TestStateInterfaceMock> state;
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;

    EXPECT_CALL(compositeState, entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, handleEvent1(&stateMachine))
        .Times(1)
        .WillOnce(DoStateChange(&compositeState,&state));
    EXPECT_CALL(compositeState, endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(state, entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state, startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state, endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state, exitImpl(&stateMachine))
        .Times(1);

    //    stateMachine.enableLogs(true);
//    compositeState.enableLogs(true);

    stateMachine.setInitialState(&compositeState);
    stateMachine.initialize();
    stateMachine.triggerEvent1();
    stateMachine.finalize();

}

TEST_F(TestCompositeStateShallowHistory,ResumeStateHistory)
{
    ::testing::NiceMock<TestCompositeStateShallowHistoryMock> compositeState;
    ::testing::NiceMock<TestStateInterfaceMock> state;
    ::testing::NiceMock<TestInnerStateInterfaceShallowHistoryMock> innerState1;
    ::testing::NiceMock<TestInnerStateInterfaceShallowHistoryMock> innerState2;
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;

    EXPECT_CALL(compositeState, entryImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState, startDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState, handleEvent2(&stateMachine))
        .Times(1)
        .WillOnce(DoStateChange(&compositeState,&state));
    EXPECT_CALL(compositeState, endDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState, exitImpl(&stateMachine))
        .Times(2);

    EXPECT_CALL(state, entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state, startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state, handleEvent3(&stateMachine))
        .Times(1)
        .WillOnce(DoStateChange(&state,&compositeState));
    EXPECT_CALL(state, endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state, exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState1, entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1, startDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1, handleEvent1(&compositeState))
        .Times(1)
        .WillOnce(DoStateChange(&innerState1,&innerState2));
    EXPECT_CALL(innerState1, endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1, exitImpl(&compositeState))
        .Times(1);

    // Expect innerState2 is resumed after turning back to compositeState (event3)
    EXPECT_CALL(innerState2, entryImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(innerState2, startDoImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(innerState2, endDoImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(innerState2, exitImpl(&compositeState))
        .Times(2);

    //    stateMachine.enableLogs(true);
//    compositeState.enableLogs(true);

    compositeState.setInitialState(&innerState1);
    stateMachine.setInitialState(&compositeState);
    stateMachine.initialize();
    stateMachine.triggerEvent1();
    stateMachine.triggerEvent2();
    stateMachine.triggerEvent3();
    stateMachine.finalize();

}
