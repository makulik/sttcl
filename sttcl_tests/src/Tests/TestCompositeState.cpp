/*
 * TestCompositeState.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TestCompositeStateMock.h"
#include "SttclStateMachineMock.h"
#include "TestInnerStateInterfaceMock.h"

class TestCompositeState : public ::testing::Test
{
public:
	TestCompositeState()
	{
	}

	~TestCompositeState()
	{
	}

private:
};

TEST_F(TestCompositeState,Constructor)
{
    ::testing::NiceMock<TestCompositeStateMock> compositeState;
}

TEST_F(TestCompositeState,LifeCycle)
{
    ::testing::NiceMock<TestCompositeStateMock> compositeState;
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

TEST_F(TestCompositeState,EventPropagation)
{
    ::testing::NiceMock<TestInnerStateInterfaceMock> innerState("innerState");
    ::testing::NiceMock<TestCompositeStateMock> compositeState("compositeState");
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;

    EXPECT_CALL(compositeState, entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState, startDoImpl(&stateMachine))
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
    stateMachine.finalize();

}
