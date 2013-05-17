/*
 * TestCompositeStateWithArgsShallowHistory.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TestStateInterfaceWithArgsMock.h"
#include "TestCompositeStateWithArgsShallowHistoryMock.h"
#include "SttclStateMachineWithArgsMock.h"
#include "TestInnerStateInterfaceWithArgsShallowHistoryMock.h"
#include "SttclTestActions.h"

class TestCompositeStateWithArgsShallowHistory : public ::testing::Test
{
public:
	TestCompositeStateWithArgsShallowHistory()
	{
	}

	~TestCompositeStateWithArgsShallowHistory()
	{
	}

private:
};

TEST_F(TestCompositeStateWithArgsShallowHistory,Constructor)
{
    ::testing::NiceMock<TestCompositeStateWithArgsShallowHistoryMock> compositeState;
}

TEST_F(TestCompositeStateWithArgsShallowHistory,LifeCycle)
{
    ::testing::NiceMock<TestCompositeStateWithArgsShallowHistoryMock> compositeState;
    ::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;

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

TEST_F(TestCompositeStateWithArgsShallowHistory,EventPropagation)
{
    ::testing::NiceMock<TestInnerStateInterfaceWithArgsShallowHistoryMock> innerState("innerState");
    ::testing::NiceMock<TestCompositeStateWithArgsShallowHistoryMock> compositeState("compositeState");
    ::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;

    EXPECT_CALL(compositeState, entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, handleEvent1(&stateMachine,_,_))
        .Times(1);
    EXPECT_CALL(compositeState, handleEvent2(&stateMachine,_))
        .Times(1);
    EXPECT_CALL(compositeState, handleEvent3(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, handleEvent4(&stateMachine,_))
        .Times(1);
    EXPECT_CALL(compositeState, endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState, entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState, startDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState, handleEvent1(&compositeState,_,_))
        .Times(1);
    EXPECT_CALL(innerState, handleEvent2(&compositeState,_))
        .Times(1);
    EXPECT_CALL(innerState, handleEvent3(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState, handleEvent4(&compositeState,_))
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
    stateMachine.triggerEvent1(42,"Hello!");
    stateMachine.triggerEvent2(3.1514);
    stateMachine.triggerEvent3();
    stateMachine.triggerEvent4(12345);
    stateMachine.finalize();

}

TEST_F(TestCompositeStateWithArgsShallowHistory,ChangeState)
{
    ::testing::NiceMock<TestCompositeStateWithArgsShallowHistoryMock> compositeState;
    ::testing::NiceMock<TestStateInterfaceWithArgsMock> state;
    ::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;

    EXPECT_CALL(compositeState, entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, handleEvent1(&stateMachine,_,_))
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
    stateMachine.triggerEvent1(42,"Hello!");
    stateMachine.finalize();

}

TEST_F(TestCompositeStateWithArgsShallowHistory,ResumeStateHistory)
{
    ::testing::NiceMock<TestCompositeStateWithArgsShallowHistoryMock> compositeState;
    ::testing::NiceMock<TestStateInterfaceWithArgsMock> state;
    ::testing::NiceMock<TestInnerStateInterfaceWithArgsShallowHistoryMock> innerState1;
    ::testing::NiceMock<TestInnerStateInterfaceWithArgsShallowHistoryMock> innerState2;
    ::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;

    EXPECT_CALL(compositeState, entryImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState, startDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState, handleEvent2(&stateMachine,_))
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
    EXPECT_CALL(innerState1, handleEvent1(&compositeState,_,_))
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
    stateMachine.triggerEvent1(42,"Hello!");
    stateMachine.triggerEvent2(3.1415);
    stateMachine.triggerEvent3();
    stateMachine.finalize();

}
