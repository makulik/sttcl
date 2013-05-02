/*
 * TestRegion.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SttclStateMachineMock.h"
#include "TestRegionMock.h"
#include "TestConcurrentCompositeStateMock.h"

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
