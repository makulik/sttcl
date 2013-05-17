/*
 * TestInnerStateInterfaceShallowHistoryMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTINNERSTATEINTERFACESHALLOWHISTORYMOCK_H_
#define TESTINNERSTATEINTERFACESHALLOWHISTORYMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestInnerStateInterfaceShallowHistory.h"
#include "IStateMachineHooks.h"
#include "IStateHooks.h"
#include "SttclStateMock.h"
#include "SttclTestLog.h"

#include "TestCompositeStateShallowHistoryMock.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template<unsigned int NestingLevel = 1>
class TestInnerStateInterfaceShallowHistoryMock
: public SttclStateMock<TestCompositeStateShallowHistoryMock<NestingLevel - 1>,ITestInnerStateInterfaceShallowHistory<NestingLevel> >
{
public:
    typedef ITestInnerStateInterfaceShallowHistory<NestingLevel> StateInterface;
    typedef SttclStateMock<TestCompositeStateShallowHistoryMock<NestingLevel - 1>,ITestInnerStateInterfaceShallowHistory<NestingLevel> > SttclStateMockBase;

    virtual ~TestInnerStateInterfaceShallowHistoryMock() {}

    MOCK_METHOD1_T(handleEvent1, void (TestCompositeStateShallowHistoryMock<NestingLevel - 1>* context));
    MOCK_METHOD1_T(handleEvent2, void (TestCompositeStateShallowHistoryMock<NestingLevel - 1>* context));
    MOCK_METHOD1_T(handleEvent3, void (TestCompositeStateShallowHistoryMock<NestingLevel - 1>* context));
    MOCK_METHOD1_T(handleEvent4, void (TestCompositeStateShallowHistoryMock<NestingLevel - 1>* context));

    TestInnerStateInterfaceShallowHistoryMock(const std::string& stateId = "<anonymous>")
    : SttclStateMockBase(stateId)
    {
        ON_CALL(*this, handleEvent1(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceShallowHistoryMock<NestingLevel>::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceShallowHistoryMock<NestingLevel>::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceShallowHistoryMock<NestingLevel>::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceShallowHistoryMock<NestingLevel>::handleEvent4Call));

    }

    void handleEvent1Call(TestCompositeStateShallowHistoryMock<NestingLevel - 1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceShallowHistoryMock::handleEvent1Call( context = " <<
              context << ") ...");
    }

    void handleEvent2Call(TestCompositeStateShallowHistoryMock<NestingLevel - 1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceShallowHistoryMock::handleEvent2Call( context = " <<
              context << ") ...");
    }

    void handleEvent3Call(TestCompositeStateShallowHistoryMock<NestingLevel - 1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceShallowHistoryMock::handleEvent3Call( context = " <<
              context << ") ...");
    }

    void handleEvent4Call(TestCompositeStateShallowHistoryMock<NestingLevel - 1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceShallowHistoryMock::handleEvent4Call( context = " <<
              context << ") ...");
    }
};

#endif /* TESTINNERSTATEINTERFACESHALLOWHISTORYMOCK_H_ */
