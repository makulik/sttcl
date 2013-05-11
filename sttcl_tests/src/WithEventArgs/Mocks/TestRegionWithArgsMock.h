/*
 * TestRegionWithArgsMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTREGIONWITHARGSMOCK_H_
#define TESTREGIONWITHARGSMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestConcurrentStateMachineWithArgs.h"
#include "TestConcurrentCompositeStateWithArgsMock.h"
#include "SttclRegionWithArgsMock.h"
#include "SttclTestLog.h"


class SttclStateMachineMock;

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class TestRegionWithArgsMock
: public SttclRegionWithArgsMock<TestRegionWithArgsMock,TestConcurrentCompositeStateWithArgsMock,ITestConcurrentStateMachineWithArgs>
{
public:
    typedef SttclRegionWithArgsMock<TestRegionWithArgsMock,TestConcurrentCompositeStateWithArgsMock,ITestConcurrentStateMachineWithArgs> RegionMockBase;
    virtual ~TestRegionWithArgsMock()
    {
    }

    MOCK_METHOD3(handleEvent1, void (TestConcurrentCompositeStateWithArgsMock* context, ITestConcurrentStateMachineWithArgs::RegionContext* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3(handleEvent2, void (TestConcurrentCompositeStateWithArgsMock* context, ITestConcurrentStateMachineWithArgs::RegionContext* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3(handleEvent3, void (TestConcurrentCompositeStateWithArgsMock* context, ITestConcurrentStateMachineWithArgs::RegionContext* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3(handleEvent4, void (TestConcurrentCompositeStateWithArgsMock* context, ITestConcurrentStateMachineWithArgs::RegionContext* regionContext, EventArgsPtr eventArgs));

    TestRegionWithArgsMock(const std::string& stateId, TestConcurrentCompositeStateWithArgsMock* regionContainer)
    : RegionMockBase(stateId,regionContainer)
    {
        ON_CALL(*this, handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionWithArgsMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionWithArgsMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionWithArgsMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionWithArgsMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(TestConcurrentCompositeStateWithArgsMock* context, ITestConcurrentStateMachineWithArgs::RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionWithArgsMock::handleEvent1Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionWithArgsMock calling RegionMockBase::dispatchEvent() ...");
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachineWithArgs::handleEvent1,eventArgs);
        }
    }

    void handleEvent2Call(TestConcurrentCompositeStateWithArgsMock* context, ITestConcurrentStateMachineWithArgs::RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionWithArgsMock::handleEvent2Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionWithArgsMock calling RegionMockBase::dispatchEvent() ...");
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachineWithArgs::handleEvent2,eventArgs);
        }
    }

    void handleEvent3Call(TestConcurrentCompositeStateWithArgsMock* context, ITestConcurrentStateMachineWithArgs::RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionWithArgsMock::handleEvent3Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionWithArgsMock calling RegionMockBase::dispatchEvent() ...");
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachineWithArgs::handleEvent3,eventArgs);
        }
    }

    void handleEvent4Call(TestConcurrentCompositeStateWithArgsMock* context, ITestConcurrentStateMachineWithArgs::RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionWithArgsMock::handleEvent4Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG(logsEnabled(), id() << " TestRegionWithArgsMock calling RegionMockBase::dispatchEvent() ...");
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachineWithArgs::handleEvent4,eventArgs);
        }
    }
};

#endif /* TESTREGIONWITHARGSMOCK_H_ */
