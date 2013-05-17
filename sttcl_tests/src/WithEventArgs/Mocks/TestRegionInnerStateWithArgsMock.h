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

template<unsigned int NestingLevel = 1>
class TestRegionInnerStateWithArgsMock
: public SttclStateWithArgsMock<TestRegionWithArgsMock<NestingLevel>,ITestConcurrentStateMachineWithArgs<NestingLevel> >
{
public:
    typedef SttclStateWithArgsMock<TestRegionWithArgsMock<NestingLevel>,ITestConcurrentStateMachineWithArgs<NestingLevel> > SttclStateMockBase;
    typedef ITestConcurrentStateMachineWithArgs<NestingLevel> StateInterface;
    typedef typename ITestConcurrentStateMachineWithArgs<NestingLevel>::Context Context;
    typedef typename ITestConcurrentStateMachineWithArgs<NestingLevel>::RegionContext RegionContext;

    virtual ~TestRegionInnerStateWithArgsMock() {}

    MOCK_METHOD3_T(handleEvent1, void (Context* context,RegionContext* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3_T(handleEvent2, void (Context* context,RegionContext* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3_T(handleEvent3, void (Context* context,RegionContext* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3_T(handleEvent4, void (Context* context,RegionContext* regionContext, EventArgsPtr eventArgs));

    TestRegionInnerStateWithArgsMock(const std::string& stateId = "<anonymous>")
    : SttclStateWithArgsMock<TestRegionWithArgsMock<NestingLevel>,ITestConcurrentStateMachineWithArgs<NestingLevel> >(stateId)
    {
        ON_CALL(*this, handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateWithArgsMock<NestingLevel>::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateWithArgsMock<NestingLevel>::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateWithArgsMock<NestingLevel>::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateWithArgsMock<NestingLevel>::handleEvent4Call));

    }

protected:
    void handleEvent1Call(Context* context,RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , SttclStateMockBase::id() <<
              " TestRegionInnerStateMock::handleEvent1Call( context = " << context <<
              ", regionContext = " << regionContext << " ) ...");
    }

    void handleEvent2Call(Context* context,RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , SttclStateMockBase::id() <<
              " TestRegionInnerStateMock::handleEvent2Call( context = " << context <<
              ", regionContext = " << regionContext << " ) ...");
    }

    void handleEvent3Call(Context* context,RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , SttclStateMockBase::id() <<
              " TestRegionInnerStateMock::handleEvent3Call( context = " << context <<
              ", regionContext = " << regionContext << " ) ...");
    }

    void handleEvent4Call(Context* context,RegionContext* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , SttclStateMockBase::id() <<
              " TestRegionInnerStateMock::handleEvent4Call( context = " << context <<
              ", regionContext = " << regionContext << " ) ...");
    }
};

#endif /* TESTREGIONINNERSTATEWITHARGSMOCK_H_ */
