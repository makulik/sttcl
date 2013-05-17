/*
 * TestInnerStateInterfaceMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTINNERSTATEINTERFACEMOCK_H_
#define TESTINNERSTATEINTERFACEMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestInnerStateInterface.h"
#include "IStateMachineHooks.h"
#include "IStateHooks.h"
#include "SttclStateMock.h"
#include "SttclTestLog.h"

#include "TestCompositeStateMock.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template<unsigned int NestingLevel = 1>
class TestInnerStateInterfaceMock
: public SttclStateMock<TestCompositeStateMock<NestingLevel - 1>,ITestInnerStateInterface<NestingLevel> >
{
public:
    typedef ITestInnerStateInterface<NestingLevel> StateInterface;
    typedef SttclStateMock<TestCompositeStateMock<NestingLevel - 1>,ITestInnerStateInterface<NestingLevel> > SttclStateMockBase;

    virtual ~TestInnerStateInterfaceMock() {}

    MOCK_METHOD1_T(handleEvent1, void (TestCompositeStateMock<NestingLevel -1>* context));
    MOCK_METHOD1_T(handleEvent2, void (TestCompositeStateMock<NestingLevel -1>* context));
    MOCK_METHOD1_T(handleEvent3, void (TestCompositeStateMock<NestingLevel -1>* context));
    MOCK_METHOD1_T(handleEvent4, void (TestCompositeStateMock<NestingLevel -1>* context));

    TestInnerStateInterfaceMock(const std::string& stateId = "<anonymous>")
    : SttclStateMock<TestCompositeStateMock<NestingLevel - 1>,ITestInnerStateInterface<NestingLevel> >(stateId)
    {
        ON_CALL(*this, handleEvent1(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(TestCompositeStateMock<NestingLevel -1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceMock::handleEvent1Call( context = " <<
              context << ") ...");
    }

    void handleEvent2Call(TestCompositeStateMock<NestingLevel -1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceMock::handleEvent2Call( context = " <<
              context << ") ...");
    }

    void handleEvent3Call(TestCompositeStateMock<NestingLevel -1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceMock::handleEvent3Call( context = " <<
              context << ") ...");
    }

    void handleEvent4Call(TestCompositeStateMock<NestingLevel -1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceMock::handleEvent4Call( context = " <<
              context << ") ...");
    }
};

#endif /* TESTINNERSTATEINTERFACEMOCK_H_ */
