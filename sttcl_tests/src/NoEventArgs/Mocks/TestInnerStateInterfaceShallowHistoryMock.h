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

class TestInnerStateInterfaceShallowHistoryMock
: public SttclStateMock<TestCompositeStateShallowHistoryMock,ITestInnerStateInterfaceShallowHistory>
{
public:
    typedef ITestInnerStateInterfaceShallowHistory StateInterface;

    virtual ~TestInnerStateInterfaceShallowHistoryMock() {}

    MOCK_METHOD1(handleEvent1, void (TestCompositeStateShallowHistoryMock* context));
    MOCK_METHOD1(handleEvent2, void (TestCompositeStateShallowHistoryMock* context));
    MOCK_METHOD1(handleEvent3, void (TestCompositeStateShallowHistoryMock* context));
    MOCK_METHOD1(handleEvent4, void (TestCompositeStateShallowHistoryMock* context));

    TestInnerStateInterfaceShallowHistoryMock(const std::string& stateId = "<anonymous>")
    : SttclStateMock<TestCompositeStateShallowHistoryMock,ITestInnerStateInterfaceShallowHistory>(stateId)
    {
        ON_CALL(*this, handleEvent1(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceShallowHistoryMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceShallowHistoryMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceShallowHistoryMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceShallowHistoryMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(TestCompositeStateShallowHistoryMock* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestInnerStateInterfaceShallowHistoryMock::handleEvent1Call( context = " << context << ") ...");
    }

    void handleEvent2Call(TestCompositeStateShallowHistoryMock* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestInnerStateInterfaceShallowHistoryMock::handleEvent2Call( context = " << context << ") ...");
    }

    void handleEvent3Call(TestCompositeStateShallowHistoryMock* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestInnerStateInterfaceShallowHistoryMock::handleEvent3Call( context = " << context << ") ...");
    }

    void handleEvent4Call(TestCompositeStateShallowHistoryMock* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestInnerStateInterfaceShallowHistoryMock::handleEvent4Call( context = " << context << ") ...");
    }
};

#endif /* TESTINNERSTATEINTERFACESHALLOWHISTORYMOCK_H_ */
