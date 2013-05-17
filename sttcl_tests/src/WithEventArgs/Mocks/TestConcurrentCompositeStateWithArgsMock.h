/*
 * TestConcurrentCompositeStateWithArgsMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTCONCURRENTCOMPOSITESTATEWITHARGSMOCK_H_
#define TESTCONCURRENTCOMPOSITESTATEWITHARGSMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestConcurrentStateMachineWithArgs.h"
#include "SttclConcurrentCompositeStateWithArgsMock.h"
#include "SttclTestLog.h"

class SttclStateMachineWithArgsMock;

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template<unsigned int NestingLevel = 0>
class TestConcurrentCompositeStateWithArgsMock
: public SttclConcurrentCompositeStateWithArgsMock<TestConcurrentCompositeStateWithArgsMock<NestingLevel>,SttclStateMachineWithArgsMock,ITestConcurrentStateMachineWithArgs<NestingLevel + 1> >
{
public:
    typedef SttclConcurrentCompositeStateWithArgsMock<TestConcurrentCompositeStateWithArgsMock<NestingLevel>,SttclStateMachineWithArgsMock,ITestConcurrentStateMachineWithArgs<NestingLevel + 1> > CompositeStateMockBase;
    typedef SttclStateMachineWithArgsMock StateMachineContext;

    virtual ~TestConcurrentCompositeStateWithArgsMock()
    {
    }

    // ITestStateInterfaceWithArgs
    MOCK_METHOD3_T(handleEvent1, void (StateMachineContext* context, int arg1, const std::string& arg2));
    MOCK_METHOD2_T(handleEvent2, void (StateMachineContext* context, double arg1));
    MOCK_METHOD1_T(handleEvent3, void (StateMachineContext* context));
    MOCK_METHOD2_T(handleEvent4, void (StateMachineContext* context, int arg1));


    TestConcurrentCompositeStateWithArgsMock(SttclStateMachineWithArgsMock* context, const std::string& stateId = "<anonymous>")
    : CompositeStateMockBase(context,stateId)
    {
        ON_CALL(*this, handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateWithArgsMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateWithArgsMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateWithArgsMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateWithArgsMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(SttclStateMachineWithArgsMock* context, int arg1, const std::string& arg2)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              CompositeStateMockBase::id() <<
              " TestConcurrentCompositeStateWithArgsMock::handleEvent1Call( context = " <<
              context << ") ...");
        CompositeStateMockBase::broadcastEvent(context,&ITestConcurrentStateMachineWithArgs<NestingLevel + 1>::handleEvent1,EventArgsPtr(new Event1Args(arg1,arg2)));
    }

    void handleEvent2Call(SttclStateMachineWithArgsMock* context, double arg1)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              CompositeStateMockBase::id() <<
              " TestConcurrentCompositeStateWithArgsMock::handleEvent2Call( context = " <<
              context << ") ...");
        CompositeStateMockBase::broadcastEvent(context,&ITestConcurrentStateMachineWithArgs<NestingLevel + 1>::handleEvent2,EventArgsPtr(new Event2Args(arg1)));
    }

    void handleEvent3Call(SttclStateMachineWithArgsMock* context)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              CompositeStateMockBase::id() <<
              " TestConcurrentCompositeStateWithArgsMock::handleEvent3Call( context = " <<
              context << ") ...");
        CompositeStateMockBase::broadcastEvent(context,&ITestConcurrentStateMachineWithArgs<NestingLevel + 1>::handleEvent3,EventArgsPtr(new Event3Args()));
    }

    void handleEvent4Call(SttclStateMachineWithArgsMock* context, int arg1)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              CompositeStateMockBase::id() <<
              " TestConcurrentCompositeStateWithArgsMock::handleEvent4Call( context = " <<
              context << ") ...");
        CompositeStateMockBase::broadcastEvent(context,&ITestConcurrentStateMachineWithArgs<NestingLevel + 1>::handleEvent4,EventArgsPtr(new Event4Args(arg1)));
    }
};

#endif /* TESTCONCURRENTCOMPOSITESTATEWITHARGSMOCK_H_ */
