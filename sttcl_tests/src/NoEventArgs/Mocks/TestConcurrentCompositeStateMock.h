/*
 * TestConcurrentCompositeStateMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTCONCURRENTCOMPOSITESTATEMOCK_H_
#define TESTCONCURRENTCOMPOSITESTATEMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestConcurrentStateMachine.h"
#include "SttclConcurrentCompositeStateMock.h"
#include "SttclTestLog.h"

class SttclStateMachineMock;

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template<unsigned int NestingLevel = 0>
class TestConcurrentCompositeStateMock
: public SttclConcurrentCompositeStateMock<TestConcurrentCompositeStateMock<NestingLevel>,SttclStateMachineMock,ITestConcurrentStateMachine<NestingLevel + 1> >
{
public:
    typedef SttclConcurrentCompositeStateMock<TestConcurrentCompositeStateMock<NestingLevel>,SttclStateMachineMock,ITestConcurrentStateMachine<NestingLevel + 1> > CompositeStateMockBase;
    virtual ~TestConcurrentCompositeStateMock()
    {
    }

    MOCK_METHOD1(handleEvent1, void (SttclStateMachineMock* context));
    MOCK_METHOD1(handleEvent2, void (SttclStateMachineMock* context));
    MOCK_METHOD1(handleEvent3, void (SttclStateMachineMock* context));
    MOCK_METHOD1(handleEvent4, void (SttclStateMachineMock* context));

    TestConcurrentCompositeStateMock(SttclStateMachineMock* context, const std::string& stateId = "<anonymous>")
    : CompositeStateMockBase(context,stateId)
    {
        ON_CALL(*this, handleEvent1(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(SttclStateMachineMock* context)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              CompositeStateMockBase::id() <<
              " TestConcurrentCompositeStateMock::handleEvent1Call( context = " <<
              context << ") ...");
        CompositeStateMockBase::broadcastEvent(context,&ITestConcurrentStateMachine<NestingLevel +1>::handleEvent1);
    }

    void handleEvent2Call(SttclStateMachineMock* context)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              CompositeStateMockBase::id() <<
              " TestConcurrentCompositeStateMock::handleEvent2Call( context = " <<
              context << ") ...");
        CompositeStateMockBase::broadcastEvent(context,&ITestConcurrentStateMachine<NestingLevel +1>::handleEvent2);
    }

    void handleEvent3Call(SttclStateMachineMock* context)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              CompositeStateMockBase::id() <<
              " TestConcurrentCompositeStateMock::handleEvent3Call( context = " <<
              context << ") ...");
        CompositeStateMockBase::broadcastEvent(context,&ITestConcurrentStateMachine<NestingLevel +1>::handleEvent3);
    }

    void handleEvent4Call(SttclStateMachineMock* context)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , CompositeStateMockBase::id() <<
              " TestConcurrentCompositeStateMock::handleEvent4Call( context = " <<
              context << ") ...");
        CompositeStateMockBase::broadcastEvent(context,&ITestConcurrentStateMachine<NestingLevel +1>::handleEvent4);
    }
};

#endif /* TESTCONCURRENTCOMPOSITESTATEMOCK_H_ */
