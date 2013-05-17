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

template<unsigned int NestingLevel = 1>
class TestRegionWithArgsMock
: public SttclRegionWithArgsMock<TestRegionWithArgsMock<NestingLevel>,TestConcurrentCompositeStateWithArgsMock<NestingLevel - 1>,ITestConcurrentStateMachineWithArgs<NestingLevel>,NestingLevel>
{
public:
    typedef SttclRegionWithArgsMock<TestRegionWithArgsMock<NestingLevel>,TestConcurrentCompositeStateWithArgsMock<NestingLevel - 1>,ITestConcurrentStateMachineWithArgs<NestingLevel>,NestingLevel> RegionMockBase;
    typedef typename RegionMockBase::InnerStateClass InnerStateBaseClass;

    virtual ~TestRegionWithArgsMock()
    {
    }

    MOCK_METHOD3_T(handleEvent1, void (TestConcurrentCompositeStateWithArgsMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachineWithArgs<NestingLevel>::RegionContext* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3_T(handleEvent2, void (TestConcurrentCompositeStateWithArgsMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachineWithArgs<NestingLevel>::RegionContext* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3_T(handleEvent3, void (TestConcurrentCompositeStateWithArgsMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachineWithArgs<NestingLevel>::RegionContext* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3_T(handleEvent4, void (TestConcurrentCompositeStateWithArgsMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachineWithArgs<NestingLevel>::RegionContext* regionContext, EventArgsPtr eventArgs));

    TestRegionWithArgsMock(const std::string& stateId, TestConcurrentCompositeStateWithArgsMock<NestingLevel - 1>* regionContainer)
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
    void handleEvent1Call(TestConcurrentCompositeStateWithArgsMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachineWithArgs<NestingLevel>::RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG
            ( RegionMockBase::logsEnabled()
            , RegionMockBase::id() <<
              " TestRegionMock::handleEvent1Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = RegionMockBase::getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG
                ( RegionMockBase::logsEnabled()
                , RegionMockBase::id() <<
                  " TestRegionMock calling RegionMockBase::dispatchEvent() ...");
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachineWithArgs<NestingLevel>::handleEvent1,eventArgs);
        }
    }

    void handleEvent2Call(TestConcurrentCompositeStateWithArgsMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachineWithArgs<NestingLevel>::RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG
            ( RegionMockBase::logsEnabled()
            , RegionMockBase::id() <<
              " TestRegionMock::handleEvent2Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = RegionMockBase::getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG
                ( RegionMockBase::logsEnabled()
                , RegionMockBase::id() <<
                  " TestRegionMock calling RegionMockBase::dispatchEvent() ...");
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachineWithArgs<NestingLevel>::handleEvent2,eventArgs);
        }
    }

    void handleEvent3Call(TestConcurrentCompositeStateWithArgsMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachineWithArgs<NestingLevel>::RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG
            ( RegionMockBase::logsEnabled()
            , RegionMockBase::id() <<
              " TestRegionMock::handleEvent3Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = RegionMockBase::getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG
                ( RegionMockBase::logsEnabled()
                , RegionMockBase::id() <<
                  " TestRegionMock calling RegionMockBase::dispatchEvent() ...");
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachineWithArgs<NestingLevel>::handleEvent3,eventArgs);
        }
    }

    void handleEvent4Call(TestConcurrentCompositeStateWithArgsMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachineWithArgs<NestingLevel>::RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG
            ( RegionMockBase::logsEnabled()
            , RegionMockBase::id() <<
              " TestRegionMock::handleEvent4Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = RegionMockBase::getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG
                ( RegionMockBase::logsEnabled()
                , RegionMockBase::id() <<
                  " TestRegionMock calling RegionMockBase::dispatchEvent() ...");
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachineWithArgs<NestingLevel>::handleEvent4,eventArgs);
        }
    }
};

#endif /* TESTREGIONWITHARGSMOCK_H_ */
