/*
 * TestRegionInnerStateWithArgsMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTREGIONINNERSTATEWITHARGSMOCK_H_
#define TESTREGIONINNERSTATEWITHARGSMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestConcurrentStateMachineWithArgs.h"
#include "SttclStateWithArgsMock.h"
#include "TestRegionWithArgsMock.h"
#include "SttclTestLog.h"

#include "TestCompositeStateWithArgsMock.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class TestRegionInnerStateWithArgsMock
: public SttclStateWithArgsMock<TestRegionWithArgsMock,ITestConcurrentStateMachineWithArgs>
{
public:
    typedef ITestConcurrentStateMachineWithArgs StateInterface;

    virtual ~TestRegionInnerStateWithArgsMock() {}

    MOCK_METHOD3(handleEvent1, void (TestConcurrentCompositeStateWithArgsMock* context,RegionContext* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3(handleEvent2, void (TestConcurrentCompositeStateWithArgsMock* context,RegionContext* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3(handleEvent3, void (TestConcurrentCompositeStateWithArgsMock* context,RegionContext* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3(handleEvent4, void (TestConcurrentCompositeStateWithArgsMock* context,RegionContext* regionContext, EventArgsPtr eventArgs));

    TestRegionInnerStateWithArgsMock(const std::string& stateId = "<anonymous>")
    : SttclStateWithArgsMock<TestRegionWithArgsMock,ITestConcurrentStateMachineWithArgs>(stateId)
    {
        ON_CALL(*this, handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateWithArgsMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateWithArgsMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateWithArgsMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateWithArgsMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(TestConcurrentCompositeStateWithArgsMock* context,RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionInnerStateWithArgsMock::handleEvent1Call( context = " << context << ", regionContext = " << regionContext << " ) ...");
    }

    void handleEvent2Call(TestConcurrentCompositeStateWithArgsMock* context,RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionInnerStateWithArgsMock::handleEvent2Call( context = " << context << ", regionContext = " << regionContext << " ) ...");
    }

    void handleEvent3Call(TestConcurrentCompositeStateWithArgsMock* context,RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionInnerStateWithArgsMock::handleEvent3Call( context = " << context << ", regionContext = " << regionContext << " ) ...");
    }

    void handleEvent4Call(TestConcurrentCompositeStateWithArgsMock* context,RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionInnerStateWithArgsMock::handleEvent4Call( context = " << context << ", regionContext = " << regionContext << " ) ...");
    }
};

#endif /* TESTREGIONINNERSTATEWITHARGSMOCK_H_ */
