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
    ::testing::NiceMock<TestConcurrentCompositeStateMock> concurrentCompositeState(&stateMachine,"concurrentCompositeState");
    ::testing::NiceMock<TestRegionMock> region1("region1",&concurrentCompositeState);
}

TEST_F(TestRegion,LifeCycle)
{
    ::testing::NiceMock<SttclStateMachineMock> stateMachine;
    stateMachine.enableLogs(true);
    ::testing::NiceMock<TestConcurrentCompositeStateMock> concurrentCompositeState(&stateMachine,"concurrentCompositeState");
    concurrentCompositeState.enableLogs(true);
    ::testing::NiceMock<TestRegionInnerStateMock> regionInnerState("innerState");
    regionInnerState.enableLogs(true);
    ::testing::NiceMock<TestRegionMock> region1("region1",&concurrentCompositeState);
    region1.enableLogs(true);

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
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,1));
    stateMachine.finalize();
    ASSERT_TRUE(region1.waitForDoActionExited(sttcl::TimeDuration<>(0,0,0,500),20));
}
