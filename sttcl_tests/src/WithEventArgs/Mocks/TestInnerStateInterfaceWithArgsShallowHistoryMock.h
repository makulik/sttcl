/*
 * TestInnerStateInterfaceWithArgsShallowHistoryMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTINNERSTATEINTERFACEWITHARGSSHALLOWHISTORYMOCK_H_
#define TESTINNERSTATEINTERFACEWITHARGSSHALLOWHISTORYMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestInnerStateInterfaceWithArgsShallowHistory.h"
#include "IStateMachineHooks.h"
#include "IStateHooks.h"
#include "SttclStateMock.h"
#include "SttclTestLog.h"

#include "TestCompositeStateWithArgsShallowHistoryMock.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template<unsigned int NestingLevel = 1>
class TestInnerStateInterfaceWithArgsShallowHistoryMock
: public SttclStateMock<TestCompositeStateWithArgsShallowHistoryMock<NestingLevel - 1>,ITestInnerStateInterfaceWithArgsShallowHistory<NestingLevel> >
{
public:
    typedef SttclStateMock<TestCompositeStateWithArgsShallowHistoryMock<NestingLevel - 1>,ITestInnerStateInterfaceWithArgsShallowHistory<NestingLevel> > SttclStateMockBase;
    typedef ITestInnerStateInterfaceWithArgsShallowHistory<NestingLevel> StateInterface;

    virtual ~TestInnerStateInterfaceWithArgsShallowHistoryMock() {}

    MOCK_METHOD3_T(handleEvent1, void (TestCompositeStateWithArgsShallowHistoryMock<NestingLevel - 1>* context, int arg1, const  std::string& arg2));
    MOCK_METHOD2_T(handleEvent2, void (TestCompositeStateWithArgsShallowHistoryMock<NestingLevel - 1>* context, double arg1));
    MOCK_METHOD1_T(handleEvent3, void (TestCompositeStateWithArgsShallowHistoryMock<NestingLevel - 1>* context));
    MOCK_METHOD2_T(handleEvent4, void (TestCompositeStateWithArgsShallowHistoryMock<NestingLevel - 1>* context, int arg1));

    TestInnerStateInterfaceWithArgsShallowHistoryMock(const std::string& stateId = "<anonymous>")
    : SttclStateMockBase(stateId)
    {
        ON_CALL(*this, handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceWithArgsShallowHistoryMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceWithArgsShallowHistoryMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceWithArgsShallowHistoryMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceWithArgsShallowHistoryMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(TestCompositeStateWithArgsShallowHistoryMock<NestingLevel - 1>* context, int arg1, const std::string& arg2)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceWithArgsMock::handleEvent1Call( context = " <<
              context << ", arg1 = " << arg1 << ", arg2 = " << arg2 << ") ...");
    }

    void handleEvent2Call(TestCompositeStateWithArgsShallowHistoryMock<NestingLevel - 1>* context, double arg1)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceWithArgsMock::handleEvent2Call( context = " <<
              context << ", arg1 = " << arg1 << ") ...");
    }

    void handleEvent3Call(TestCompositeStateWithArgsShallowHistoryMock<NestingLevel - 1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceWithArgsMock::handleEvent3Call( context = " <<
              context << ") ...");
    }

    void handleEvent4Call(TestCompositeStateWithArgsShallowHistoryMock<NestingLevel - 1>* context, int arg1)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceWithArgsMock::handleEvent4Call( context = " <<
              context << ", arg1 = " << arg1 << ") ...");
    }
};

#endif /* TESTINNERSTATEINTERFACEWITHARGSSHALLOWHISTORYMOCK_H_ */
