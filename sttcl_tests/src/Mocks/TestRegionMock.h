/*
 * TestRegionMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTREGIONMOCK_H_
#define TESTREGIONMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestConcurrentStateMachine.h"
#include "TestConcurrentCompositeStateMock.h"
#include "SttclRegionMock.h"
#include "SttclTestLog.h"


class SttclStateMachineMock;

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class TestRegionMock
: public SttclRegionMock<TestRegionMock,TestConcurrentCompositeStateMock,ITestConcurrentStateMachine>
{
public:
    typedef SttclRegionMock<TestRegionMock,TestConcurrentCompositeStateMock,ITestConcurrentStateMachine> RegionMockBase;
    virtual ~TestRegionMock()
    {
    }

    MOCK_METHOD2(handleEvent1, void (TestConcurrentCompositeStateMock* context, ITestConcurrentStateMachine::RegionContext* regionContext));
    MOCK_METHOD2(handleEvent2, void (TestConcurrentCompositeStateMock* context, ITestConcurrentStateMachine::RegionContext* regionContext));
    MOCK_METHOD2(handleEvent3, void (TestConcurrentCompositeStateMock* context, ITestConcurrentStateMachine::RegionContext* regionContext));
    MOCK_METHOD2(handleEvent4, void (TestConcurrentCompositeStateMock* context, ITestConcurrentStateMachine::RegionContext* regionContext));

    TestRegionMock(const std::string& stateId, TestConcurrentCompositeStateMock* regionContainer)
    : RegionMockBase(stateId,regionContainer)
    {
        ON_CALL(*this, handleEvent1(_,_))
            .WillByDefault(Invoke(this, &TestRegionMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestRegionMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_,_))
            .WillByDefault(Invoke(this, &TestRegionMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestRegionMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(TestConcurrentCompositeStateMock* context, ITestConcurrentStateMachine::RegionContext* regionContext)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionMock::handleEvent1Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionMock calling RegionMockBase::dispatchEvent() ...");
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachine::handleEvent1);
        }
    }

    void handleEvent2Call(TestConcurrentCompositeStateMock* context, ITestConcurrentStateMachine::RegionContext* regionContext)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionMock::handleEvent2Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionMock calling RegionMockBase::dispatchEvent() ...");
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachine::handleEvent2);
        }
    }

    void handleEvent3Call(TestConcurrentCompositeStateMock* context, ITestConcurrentStateMachine::RegionContext* regionContext)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionMock::handleEvent3Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionMock calling RegionMockBase::dispatchEvent() ...");
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachine::handleEvent3);
        }
    }

    void handleEvent4Call(TestConcurrentCompositeStateMock* context, ITestConcurrentStateMachine::RegionContext* regionContext)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionMock::handleEvent4Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionMock calling RegionMockBase::dispatchEvent() ...");
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachine::handleEvent4);
        }
    }
};

#endif /* TESTREGIONMOCK_H_ */
