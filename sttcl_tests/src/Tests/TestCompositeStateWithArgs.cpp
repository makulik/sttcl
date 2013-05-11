/*
 * TestCompositeState.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TestCompositeStateWithArgsMock.h"
#include "SttclStateMachineWithArgsMock.h"
#include "TestInnerStateInterfaceWithArgsMock.h"

class TestCompositeStateWithArgs: public ::testing::Test
{
public:
    TestCompositeStateWithArgs()
    {
    }

    ~TestCompositeStateWithArgs()
    {
    }

private:
};

TEST_F(TestCompositeStateWithArgs,Constructor)
{
    ::testing::NiceMock<TestCompositeStateWithArgsMock> compositeState;
}

TEST_F(TestCompositeStateWithArgs,LifeCycle)
{
    ::testing::NiceMock<TestCompositeStateWithArgsMock> compositeState;
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

TEST_F(TestCompositeStateWithArgs,EventPropagation)
{
    ::testing::NiceMock<TestInnerStateInterfaceWithArgsMock> innerState("innerState");
    ::testing::NiceMock<TestCompositeStateWithArgsMock> compositeState("compositeState");
    ::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;

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
    EXPECT_CALL(innerState, handleEvent1(&compositeState,42,"Hello!"))
        .Times(1);
    EXPECT_CALL(innerState, handleEvent2(&compositeState,3.1415))
        .Times(1);
    EXPECT_CALL(innerState, handleEvent3(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState, handleEvent4(&compositeState,12345))
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
    stateMachine.triggerEvent2(3.1415);
    stateMachine.triggerEvent3();
    stateMachine.triggerEvent4(12345);
    stateMachine.finalize();

}
