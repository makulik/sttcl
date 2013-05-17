/*
 * TestInnerStateInterfaceDeepHistoryMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTINNERSTATEINTERFACEDEEPHISTORYMOCK_H_
#define TESTINNERSTATEINTERFACEDEEPHISTORYMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestInnerStateInterfaceDeepHistory.h"
#include "IStateMachineHooks.h"
#include "IStateHooks.h"
#include "SttclStateMock.h"
#include "SttclTestLog.h"

#include "TestCompositeStateDeepHistoryMock.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template<unsigned int NestingLevel = 1>
class TestInnerStateInterfaceDeepHistoryMock
: public SttclStateMock<TestCompositeStateDeepHistoryMock<NestingLevel - 1>,ITestInnerStateInterfaceDeepHistory<NestingLevel> >
{
public:
    typedef ITestInnerStateInterfaceDeepHistory<NestingLevel> StateInterface;
    typedef SttclStateMock<TestCompositeStateDeepHistoryMock<NestingLevel - 1>,ITestInnerStateInterfaceDeepHistory<NestingLevel> > SttclStateMockBase;

    virtual ~TestInnerStateInterfaceDeepHistoryMock() {}

    MOCK_METHOD1_T(handleEvent1, void (TestCompositeStateDeepHistoryMock<NestingLevel - 1>* context));
    MOCK_METHOD1_T(handleEvent2, void (TestCompositeStateDeepHistoryMock<NestingLevel - 1>* context));
    MOCK_METHOD1_T(handleEvent3, void (TestCompositeStateDeepHistoryMock<NestingLevel - 1>* context));
    MOCK_METHOD1_T(handleEvent4, void (TestCompositeStateDeepHistoryMock<NestingLevel - 1>* context));

    TestInnerStateInterfaceDeepHistoryMock(const std::string& stateId = "<anonymous>")
    : SttclStateMockBase(stateId)
    {
        ON_CALL(*this, handleEvent1(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceDeepHistoryMock<NestingLevel>::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceDeepHistoryMock<NestingLevel>::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceDeepHistoryMock<NestingLevel>::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceDeepHistoryMock<NestingLevel>::handleEvent4Call));

    }

    void handleEvent1Call(TestCompositeStateDeepHistoryMock<NestingLevel - 1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceDeepHistoryMock::handleEvent1Call( context = " <<
              context << ") ...");
    }

    void handleEvent2Call(TestCompositeStateDeepHistoryMock<NestingLevel - 1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceDeepHistoryMock::handleEvent2Call( context = " <<
              context << ") ...");
    }

    void handleEvent3Call(TestCompositeStateDeepHistoryMock<NestingLevel - 1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceDeepHistoryMock::handleEvent3Call( context = " <<
              context << ") ...");
    }

    void handleEvent4Call(TestCompositeStateDeepHistoryMock<NestingLevel - 1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceDeepHistoryMock::handleEvent4Call( context = " <<
              context << ") ...");
    }
};

#endif /* TESTINNERSTATEINTERFACEDEEPHISTORYMOCK_H_ */
