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

template<unsigned int NestingLevel = 1>
class TestRegionMock
: public SttclRegionMock<TestRegionMock<NestingLevel>,TestConcurrentCompositeStateMock<NestingLevel - 1>,ITestConcurrentStateMachine<NestingLevel>,NestingLevel>
{
public:
    typedef SttclRegionMock<TestRegionMock,TestConcurrentCompositeStateMock<NestingLevel - 1>,ITestConcurrentStateMachine<NestingLevel>,NestingLevel> RegionMockBase;
    typedef typename RegionMockBase::InnerStateClass InnerStateBaseClass;

    virtual ~TestRegionMock()
    {
    }

    MOCK_METHOD2_T(handleEvent1, void (TestConcurrentCompositeStateMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachine<NestingLevel>::RegionContext* regionContext));
    MOCK_METHOD2_T(handleEvent2, void (TestConcurrentCompositeStateMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachine<NestingLevel>::RegionContext* regionContext));
    MOCK_METHOD2_T(handleEvent3, void (TestConcurrentCompositeStateMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachine<NestingLevel>::RegionContext* regionContext));
    MOCK_METHOD2_T(handleEvent4, void (TestConcurrentCompositeStateMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachine<NestingLevel>::RegionContext* regionContext));

    TestRegionMock(const std::string& stateId, TestConcurrentCompositeStateMock<NestingLevel - 1>* regionContainer)
    : RegionMockBase(stateId,regionContainer)
    {
        ON_CALL(*this, handleEvent1(_,_))
            .WillByDefault(Invoke(this, &TestRegionMock<NestingLevel>::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestRegionMock<NestingLevel>::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_,_))
            .WillByDefault(Invoke(this, &TestRegionMock<NestingLevel>::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestRegionMock<NestingLevel>::handleEvent4Call));

    }

protected:
    void handleEvent1Call(TestConcurrentCompositeStateMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachine<NestingLevel>::RegionContext* regionContext)
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
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachine<NestingLevel>::handleEvent1);
        }
    }

    void handleEvent2Call(TestConcurrentCompositeStateMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachine<NestingLevel>::RegionContext* regionContext)
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
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachine<NestingLevel>::handleEvent2);
        }
    }

    void handleEvent3Call(TestConcurrentCompositeStateMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachine<NestingLevel>::RegionContext* regionContext)
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
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachine<NestingLevel>::handleEvent3);
        }
    }

    void handleEvent4Call(TestConcurrentCompositeStateMock<NestingLevel - 1>* context, typename ITestConcurrentStateMachine<NestingLevel>::RegionContext* regionContext)
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
            RegionMockBase::dispatchEvent(context,currentState,&ITestConcurrentStateMachine<NestingLevel>::handleEvent4);
        }
    }
};

#endif /* TESTREGIONMOCK_H_ */
