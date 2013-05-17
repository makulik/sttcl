/*
 * TestRegion.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unistd.h>
#include "SttclStateMachineMock.h"
#include "TestRegionMock.h"
#include "TestConcurrentCompositeStateMock.h"
#include "TestRegionInnerStateMock.h"
#include "SttclTestAsyncActions.h"

class TestRegion : public ::testing::Test
{
public:
	TestRegion()
	{
	}

	~TestRegion()
	{
	}

private:
};

TEST_F(TestRegion,Constructor)
{
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;
    ::testing::NiceMock<TestConcurrentCompositeStateMock<> > concurrentCompositeState(&stateMachine,"concurrentCompositeState");
    ::testing::NiceMock<TestRegionMock<> > region1("region1",&concurrentCompositeState);
}

TEST_F(TestRegion,LifeCycle)
{
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;
//    stateMachine.enableLogs(true);
    ::testing::NiceMock<TestConcurrentCompositeStateMock<> > concurrentCompositeState(&stateMachine,"concurrentCompositeState");
//    concurrentCompositeState.enableLogs(true);
    ::testing::NiceMock<TestRegionInnerStateMock<> > regionInnerState("innerState");
//    regionInnerState.enableLogs(true);
    ::testing::NiceMock<TestRegionMock<> > region1("region1",&concurrentCompositeState);
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

TEST_F(TestRegion,LifeCycle_2)
{
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;
//    stateMachine.enableLogs(true);
    ::testing::NiceMock<TestConcurrentCompositeStateMock<> > concurrentCompositeState(&stateMachine,"concurrentCompositeState");
//    concurrentCompositeState.enableLogs(true);
    ::testing::NiceMock<TestRegionInnerStateMock<> > region1InnerState("region1InnerState");
//    region1InnerState.enableLogs(true);
    ::testing::NiceMock<TestRegionInnerStateMock<> > region2InnerState("region2InnerState");
//    region2InnerState.enableLogs(true);
    ::testing::NiceMock<TestRegionMock<> > region1("region1",&concurrentCompositeState);
//    region1.enableLogs(true);
    ::testing::NiceMock<TestRegionMock<> > region2("region2",&concurrentCompositeState);
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

TEST_F(TestRegion,EventPropagation)
{
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;
//    stateMachine.enableLogs(true);
    ::testing::NiceMock<TestConcurrentCompositeStateMock<>> concurrentCompositeState(&stateMachine,"concurrentCompositeState");
//    concurrentCompositeState.enableLogs(true);
    ::testing::NiceMock<TestRegionInnerStateMock<> > region1InnerState("region1InnerState");
//    region1InnerState.enableLogs(true);
    ::testing::NiceMock<TestRegionInnerStateMock<> > region2InnerState("region2InnerState");
//    region2InnerState.enableLogs(true);
    ::testing::NiceMock<TestRegionMock<> > region1("region1",&concurrentCompositeState);
//    region1.enableLogs(true);
    ::testing::NiceMock<TestRegionMock<> > region2("region2",&concurrentCompositeState);
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
    EXPECT_CALL(region1InnerState, handleEvent1(_,_))
        .Times(1);
    EXPECT_CALL(region1InnerState, handleEvent2(_,_))
        .Times(1);
    EXPECT_CALL(region1InnerState, handleEvent3(_,_))
        .Times(1);
    EXPECT_CALL(region1InnerState, handleEvent4(_,_))
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
    EXPECT_CALL(region2InnerState, handleEvent1(_,_))
        .Times(1);
    EXPECT_CALL(region2InnerState, handleEvent2(_,_))
        .Times(1);
    EXPECT_CALL(region2InnerState, handleEvent3(_,_))
        .Times(1);
    EXPECT_CALL(region2InnerState, handleEvent4(_,_))
        .Times(1);
    EXPECT_CALL(region2InnerState, exitImpl(&region2))
        .Times(1);

    stateMachine.setInitialState(&concurrentCompositeState);
    region1.setInitialState(&region1InnerState);
    region2.setInitialState(&region2InnerState);
    concurrentCompositeState.setRegion(0,&region1);
    concurrentCompositeState.setRegion(1,&region2);

    stateMachine.initialize();
    stateMachine.triggerEvent1();
    stateMachine.triggerEvent2();
    stateMachine.triggerEvent3();
    stateMachine.triggerEvent4();
    stateMachine.finalize();
    EXPECT_TRUE(region1.waitForDoActionExited(sttcl::TimeDuration<>(0,0,2)));
    EXPECT_TRUE(region2.waitForDoActionExited(sttcl::TimeDuration<>(0,0,2)));
}
