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

class TestInnerStateInterfaceWithArgsShallowHistoryMock
: public SttclStateMock<TestCompositeStateWithArgsShallowHistoryMock,ITestInnerStateInterfaceWithArgsShallowHistory>
{
public:
    typedef ITestInnerStateInterfaceWithArgsShallowHistory StateInterface;

    virtual ~TestInnerStateInterfaceWithArgsShallowHistoryMock() {}

    MOCK_METHOD3(handleEvent1, void (TestCompositeStateWithArgsShallowHistoryMock* context, int arg1, const  std::string& arg2));
    MOCK_METHOD2(handleEvent2, void (TestCompositeStateWithArgsShallowHistoryMock* context, double arg1));
    MOCK_METHOD1(handleEvent3, void (TestCompositeStateWithArgsShallowHistoryMock* context));
    MOCK_METHOD2(handleEvent4, void (TestCompositeStateWithArgsShallowHistoryMock* context, int arg1));

    TestInnerStateInterfaceWithArgsShallowHistoryMock(const std::string& stateId = "<anonymous>")
    : SttclStateMock<TestCompositeStateWithArgsShallowHistoryMock,ITestInnerStateInterfaceWithArgsShallowHistory>(stateId)
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
    void handleEvent1Call(TestCompositeStateWithArgsShallowHistoryMock* context, int arg1, const std::string& arg2)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestInnerStateInterfaceWithArgsShallowHistoryMock::handleEvent1Call( context = " << context << ") ...");
    }

    void handleEvent2Call(TestCompositeStateWithArgsShallowHistoryMock* context, double arg1)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestInnerStateInterfaceWithArgsShallowHistoryMock::handleEvent2Call( context = " << context << ") ...");
    }

    void handleEvent3Call(TestCompositeStateWithArgsShallowHistoryMock* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestInnerStateInterfaceWithArgsShallowHistoryMock::handleEvent3Call( context = " << context << ") ...");
    }

    void handleEvent4Call(TestCompositeStateWithArgsShallowHistoryMock* context, int arg1)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestInnerStateInterfaceWithArgsShallowHistoryMock::handleEvent4Call( context = " << context << ") ...");
    }
};

#endif /* TESTINNERSTATEINTERFACEWITHARGSSHALLOWHISTORYMOCK_H_ */
