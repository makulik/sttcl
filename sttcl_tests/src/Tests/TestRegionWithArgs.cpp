/*
 * TestRegionWithArgs.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unistd.h>
#include "SttclStateMachineWithArgsMock.h"
#include "TestRegionWithArgsMock.h"
#include "TestConcurrentCompositeStateWithArgsMock.h"
#include "TestRegionInnerStateWithArgsMock.h"
#include "SttclTestAsyncActions.h"

class TestRegionWithArgs : public ::testing::Test
{
public:
	TestRegionWithArgs()
	{
	}

	~TestRegionWithArgs()
	{
	}

private:
};

TEST_F(TestRegionWithArgs,Constructor)
{
    ::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;
    ::testing::NiceMock<TestConcurrentCompositeStateWithArgsMock<> > concurrentCompositeState(&stateMachine,"concurrentCompositeState");
    ::testing::NiceMock<TestRegionWithArgsMock<> > region1("region1",&concurrentCompositeState);
}

TEST_F(TestRegionWithArgs,LifeCycle)
{
    ::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;
//    stateMachine.enableLogs(true);
    ::testing::NiceMock<TestConcurrentCompositeStateWithArgsMock<> > concurrentCompositeState(&stateMachine,"concurrentCompositeState");
//    concurrentCompositeState.enableLogs(true);
    ::testing::NiceMock<TestRegionInnerStateWithArgsMock<> > regionInnerState("innerState");
//    regionInnerState.enableLogs(true);
    ::testing::NiceMock<TestRegionWithArgsMock<> > region1("region1",&concurrentCompositeState);
//    region1.enableLogs(true);

    EXPECT_CALL(region1, enterRegionImpl(&concurrentCompositeState))
        .Times(1);
    EXPECT_CALL(region1, startingRegionThread())
        .Times(1);
    EXPECT_CALL(region1, endingRegionThread())
        .Times(1);
    EXPECT_CALL(region1, exitRegionImpl(&concurrentCompositeState))
        .Times(1);

    stateMachine.setInitialState(&concurrentCompositeState);
    region1.setInitialState(&regionInnerState);
    concurrentCompositeState.setRegion(0,&region1);

    stateMachine.initialize();
    stateMachine.finalize();
    EXPECT_TRUE(region1.waitForDoActionExited(sttcl::TimeDuration<>(0,0,2)));
}

TEST_F(TestRegionWithArgs,LifeCycle_2)
{
    ::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;
//    stateMachine.enableLogs(true);
    ::testing::NiceMock<TestConcurrentCompositeStateWithArgsMock<> > concurrentCompositeState(&stateMachine,"concurrentCompositeState");
//    concurrentCompositeState.enableLogs(true);
    ::testing::NiceMock<TestRegionInnerStateWithArgsMock<> > region1InnerState("region1InnerState");
//    region1InnerState.enableLogs(true);
    ::testing::NiceMock<TestRegionInnerStateWithArgsMock<> > region2InnerState("region2InnerState");
//    region2InnerState.enableLogs(true);
    ::testing::NiceMock<TestRegionWithArgsMock<> > region1("region1",&concurrentCompositeState);
//    region1.enableLogs(true);
    ::testing::NiceMock<TestRegionWithArgsMock<> > region2("region2",&concurrentCompositeState);
//    region2.enableLogs(true);

    EXPECT_CALL(region1, enterRegionImpl(&concurrentCompositeState))
        .Times(1);
    EXPECT_CALL(region1, startingRegionThread())
        .Times(1);
    EXPECT_CALL(region1, endingRegionThread())
        .Times(1);
    EXPECT_CALL(region1, exitRegionImpl(&concurrentCompositeState))
        .Times(1);

    EXPECT_CALL(region2, enterRegionImpl(&concurrentCompositeState))
        .Times(1);
    EXPECT_CALL(region2, startingRegionThread())
        .Times(1);
    EXPECT_CALL(region2, endingRegionThread())
        .Times(1);
    EXPECT_CALL(region2, exitRegionImpl(&concurrentCompositeState))
        .Times(1);

    stateMachine.setInitialState(&concurrentCompositeState);
    region1.setInitialState(&region1InnerState);
    region2.setInitialState(&region2InnerState);
    concurrentCompositeState.setRegion(0,&region1);
    concurrentCompositeState.setRegion(1,&region2);

    stateMachine.initialize();
//    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,1));
    stateMachine.finalize();
    EXPECT_TRUE(region1.waitForDoActionExited(sttcl::TimeDuration<>(0,0,2)));
    EXPECT_TRUE(region2.waitForDoActionExited(sttcl::TimeDuration<>(0,0,2)));
}

TEST_F(TestRegionWithArgs,EventPropagation)
{
    ::testing::NiceMock<SttclStateMachineWithArgsMock> stateMachine;
//    stateMachine.enableLogs(true);
    ::testing::NiceMock<TestConcurrentCompositeStateWithArgsMock<> > concurrentCompositeState(&stateMachine,"concurrentCompositeState");
//    concurrentCompositeState.enableLogs(true);
    ::testing::NiceMock<TestRegionInnerStateWithArgsMock<> > region1InnerState("region1InnerState");
//    region1InnerState.enableLogs(true);
    ::testing::NiceMock<TestRegionInnerStateWithArgsMock<> > region2InnerState("region2InnerState");
//    region2InnerState.enableLogs(true);
    ::testing::NiceMock<TestRegionWithArgsMock<> > region1("region1",&concurrentCompositeState);
//    region1.enableLogs(true);
    ::testing::NiceMock<TestRegionWithArgsMock<> > region2("region2",&concurrentCompositeState);
//    region2.enableLogs(true);

    EXPECT_CALL(region1, enterRegionImpl(&concurrentCompositeState))
        .Times(1);
    EXPECT_CALL(region1, startingRegionThread())
        .Times(1);
    EXPECT_CALL(region1, endingRegionThread())
        .Times(1);
    EXPECT_CALL(region1, exitRegionImpl(&concurrentCompositeState))
        .Times(1);

    EXPECT_CALL(region1InnerState, entryImpl(&region1))
        .Times(1);
    EXPECT_CALL(region1InnerState, handleEvent1(&concurrentCompositeState,&region1,MatchesEvent1Args(42,"Hello!")))
        .Times(1);
    EXPECT_CALL(region1InnerState, handleEvent2(&concurrentCompositeState,&region1,MatchesEvent2Args(3.1415)))
        .Times(1);
    EXPECT_CALL(region1InnerState, handleEvent3(&concurrentCompositeState,&region1,MatchesEvent3Args()))
        .Times(1);
    EXPECT_CALL(region1InnerState, handleEvent4(_,_,MatchesEvent4Args(12345)))
        .Times(1);
    EXPECT_CALL(region1InnerState, exitImpl(&region1))
        .Times(1);

    EXPECT_CALL(region2, enterRegionImpl(&concurrentCompositeState))
        .Times(1);
    EXPECT_CALL(region2, startingRegionThread())
        .Times(1);
    EXPECT_CALL(region2, endingRegionThread())
        .Times(1);
    EXPECT_CALL(region2, exitRegionImpl(&concurrentCompositeState))
        .Times(1);

    EXPECT_CALL(region2InnerState, entryImpl(&region2))
        .Times(1);
    EXPECT_CALL(region2InnerState, handleEvent1(&concurrentCompositeState,&region2,MatchesEvent1Args(42,"Hello!")))
        .Times(1);
    EXPECT_CALL(region2InnerState, handleEvent2(&concurrentCompositeState,&region2,MatchesEvent2Args(3.1415)))
        .Times(1);
    EXPECT_CALL(region2InnerState, handleEvent3(&concurrentCompositeState,&region2,MatchesEvent3Args()))
        .Times(1);
    EXPECT_CALL(region2InnerState, handleEvent4(&concurrentCompositeState,&region2,MatchesEvent4Args(12345)))
        .Times(1);
    EXPECT_CALL(region2InnerState, exitImpl(&region2))
        .Times(1);

    stateMachine.setInitialState(&concurrentCompositeState);
    region1.setInitialState(&region1InnerState);
    region2.setInitialState(&region2InnerState);
    concurrentCompositeState.setRegion(0,&region1);
    concurrentCompositeState.setRegion(1,&region2);

    stateMachine.initialize();
    stateMachine.triggerEvent1(42,"Hello!");
    stateMachine.triggerEvent2(3.1415);
    stateMachine.triggerEvent3();
    stateMachine.triggerEvent4(12345);
    stateMachine.finalize();
    EXPECT_TRUE(region1.waitForDoActionExited(sttcl::TimeDuration<>(0,0,2)));
    EXPECT_TRUE(region2.waitForDoActionExited(sttcl::TimeDuration<>(0,0,2)));
}
