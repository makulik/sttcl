/*
 * TestConcurrentCompositeState.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TestConcurrentCompositeStateMock.h"
#include "SttclStateMachineMock.h"
#include "TestInnerStateInterfaceMock.h"
#include "TestStateInterfaceMock.h"
#include "SttclTestActions.h"

class TestConcurrentCompositeState : public ::testing::Test
{
public:
	TestConcurrentCompositeState()
	{
	}

	~TestConcurrentCompositeState()
	{
	}

private:
};

TEST_F(TestConcurrentCompositeState,Constructor)
{
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;
    ::testing::NiceMock<TestConcurrentCompositeStateMock> concurrentCompositeState(&stateMachine);
}

TEST_F(TestConcurrentCompositeState,LifeCycle)
{
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;
    ::testing::NiceMock<TestConcurrentCompositeStateMock> concurrentCompositeState(&stateMachine);

    EXPECT_CALL(concurrentCompositeState, entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(concurrentCompositeState, startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(concurrentCompositeState, endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(concurrentCompositeState, exitImpl(&stateMachine))
        .Times(1);

//    stateMachine.enableLogs(true);
//    compositeState.enableLogs(true);

    stateMachine.setInitialState(&concurrentCompositeState);
    stateMachine.initialize();
    stateMachine.finalize();

}

TEST_F(TestConcurrentCompositeState,ChangeState)
{
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;
    ::testing::NiceMock<TestStateInterfaceMock> state;
    ::testing::NiceMock<TestConcurrentCompositeStateMock> concurrentCompositeState(&stateMachine);

    EXPECT_CALL(concurrentCompositeState, entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(concurrentCompositeState, startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(concurrentCompositeState, handleEvent1(&stateMachine))
        .Times(1)
        .WillOnce(DoStateChange(&concurrentCompositeState,&state));
    EXPECT_CALL(concurrentCompositeState, endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(concurrentCompositeState, exitImpl(&stateMachine))
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

    stateMachine.setInitialState(&concurrentCompositeState);
    stateMachine.initialize();
    stateMachine.triggerEvent1();
    stateMachine.finalize();

}
