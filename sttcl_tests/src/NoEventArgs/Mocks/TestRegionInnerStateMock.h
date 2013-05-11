/*
 * TestRegionInnerStateMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTREGIONINNERSTATEMOCK_H_
#define TESTREGIONINNERSTATEMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestConcurrentStateMachine.h"
#include "SttclStateMock.h"
#include "TestRegionMock.h"
#include "SttclTestLog.h"

#include "TestCompositeStateMock.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class TestRegionInnerStateMock
: public SttclStateMock<TestRegionMock,ITestConcurrentStateMachine>
{
public:
    typedef ITestConcurrentStateMachine StateInterface;

    virtual ~TestRegionInnerStateMock() {}

    MOCK_METHOD2(handleEvent1, void (TestConcurrentCompositeStateMock* context,RegionContext* regionContext));
    MOCK_METHOD2(handleEvent2, void (TestConcurrentCompositeStateMock* context,RegionContext* regionContext));
    MOCK_METHOD2(handleEvent3, void (TestConcurrentCompositeStateMock* context,RegionContext* regionContext));
    MOCK_METHOD2(handleEvent4, void (TestConcurrentCompositeStateMock* context,RegionContext* regionContext));

    TestRegionInnerStateMock(const std::string& stateId = "<anonymous>")
    : SttclStateMock<TestRegionMock,ITestConcurrentStateMachine>(stateId)
    {
        ON_CALL(*this, handleEvent1(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(TestConcurrentCompositeStateMock* context,RegionContext* regionContext)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionInnerStateMock::handleEvent1Call( context = " << context << ", regionContext = " << regionContext << " ) ...");
    }

    void handleEvent2Call(TestConcurrentCompositeStateMock* context,RegionContext* regionContext)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionInnerStateMock::handleEvent2Call( context = " << context << ", regionContext = " << regionContext << " ) ...");
    }

    void handleEvent3Call(TestConcurrentCompositeStateMock* context,RegionContext* regionContext)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionInnerStateMock::handleEvent3Call( context = " << context << ", regionContext = " << regionContext << " ) ...");
    }

    void handleEvent4Call(TestConcurrentCompositeStateMock* context,RegionContext* regionContext)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionInnerStateMock::handleEvent4Call( context = " << context << ", regionContext = " << regionContext << " ) ...");
    }
};

#endif /* TESTREGIONINNERSTATEMOCK_H_ */
