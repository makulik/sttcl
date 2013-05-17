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

template<unsigned int NestingLevel = 1>
class TestRegionInnerStateMock
: public SttclStateMock<TestRegionMock<NestingLevel>,ITestConcurrentStateMachine<NestingLevel> >
{
public:
    typedef SttclStateMock<TestRegionMock<NestingLevel>,ITestConcurrentStateMachine<NestingLevel> > SttclStateMockBase;
    typedef ITestConcurrentStateMachine<NestingLevel> StateInterface;
    typedef typename ITestConcurrentStateMachine<NestingLevel>::Context Context;
    typedef typename ITestConcurrentStateMachine<NestingLevel>::RegionContext RegionContext;

    virtual ~TestRegionInnerStateMock() {}

    MOCK_METHOD2_T(handleEvent1, void (Context* context,RegionContext* regionContext));
    MOCK_METHOD2_T(handleEvent2, void (Context* context,RegionContext* regionContext));
    MOCK_METHOD2_T(handleEvent3, void (Context* context,RegionContext* regionContext));
    MOCK_METHOD2_T(handleEvent4, void (Context* context,RegionContext* regionContext));

    TestRegionInnerStateMock(const std::string& stateId = "<anonymous>")
    : SttclStateMock<TestRegionMock<NestingLevel>,ITestConcurrentStateMachine<NestingLevel> >(stateId)
    {
        ON_CALL(*this, handleEvent1(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateMock<NestingLevel>::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateMock<NestingLevel>::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateMock<NestingLevel>::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateMock<NestingLevel>::handleEvent4Call));

    }

protected:
    void handleEvent1Call(Context* context,RegionContext* regionContext)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , SttclStateMockBase::id() <<
              " TestRegionInnerStateMock::handleEvent1Call( context = " << context <<
              ", regionContext = " << regionContext << " ) ...");
    }

    void handleEvent2Call(Context* context,RegionContext* regionContext)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , SttclStateMockBase::id() <<
              " TestRegionInnerStateMock::handleEvent2Call( context = " << context <<
              ", regionContext = " << regionContext << " ) ...");
    }

    void handleEvent3Call(Context* context,RegionContext* regionContext)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , SttclStateMockBase::id() <<
              " TestRegionInnerStateMock::handleEvent3Call( context = " << context <<
              ", regionContext = " << regionContext << " ) ...");
    }

    void handleEvent4Call(Context* context,RegionContext* regionContext)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , SttclStateMockBase::id() <<
              " TestRegionInnerStateMock::handleEvent4Call( context = " << context <<
              ", regionContext = " << regionContext << " ) ...");
    }
};

#endif /* TESTREGIONINNERSTATEMOCK_H_ */
