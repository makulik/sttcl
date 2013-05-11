/*
 * TestConcurrentCompositeStateWithArgs.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TestConcurrentCompositeStateWithArgsMock.h"
#include "SttclStateMachineWithArgsMock.h"
#include "TestInnerStateInterfaceWithArgsMock.h"

class TestConcurrentCompositeStateWithArgs : public ::testing::Test
{
public:
	TestConcurrentCompositeStateWithArgs()
	{
	}

	~TestConcurrentCompositeStateWithArgs()
	{
	}

private:
};

TEST_F(TestConcurrentCompositeStateWithArgs,Constructor)
{
    ::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;
    ::testing::NiceMock<TestConcurrentCompositeStateWithArgsMock> concurrentCompositeState(&stateMachine);
}

TEST_F(TestConcurrentCompositeStateWithArgs,LifeCycle)
{
    ::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;
    ::testing::NiceMock<TestConcurrentCompositeStateWithArgsMock> concurrentCompositeState(&stateMachine);

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
