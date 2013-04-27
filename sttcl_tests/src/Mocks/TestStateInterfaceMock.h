/*
 * TestStateInterfaceMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTSTATEINTERFACEMOCK_H_
#define TESTSTATEINTERFACEMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestStateInterface.h"
#include "SttclStateMock.h"
#include "SttclTestLog.h"

class SttclStateMachineMock;

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class TestStateInterfaceMock
: public SttclStateMock<SttclStateMachineMock,ITestStateInterface>
{
public:
    typedef ITestStateInterface StateInterface;

    virtual ~TestStateInterfaceMock() {}

    MOCK_METHOD1(handleEvent1, void (ITestStateInterface::Context* context));
    MOCK_METHOD1(handleEvent2, void (ITestStateInterface::Context* context));
    MOCK_METHOD1(handleEvent3, void (ITestStateInterface::Context* context));
    MOCK_METHOD1(handleEvent4, void (ITestStateInterface::Context* context));

    TestStateInterfaceMock(const std::string& stateId = "<anonymous>")
    : SttclStateMock<SttclStateMachineMock,ITestStateInterface>(stateId)
    {
        ON_CALL(*this, handleEvent1(_))
            .WillByDefault(Invoke(this, &TestStateInterfaceMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_))
            .WillByDefault(Invoke(this, &TestStateInterfaceMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestStateInterfaceMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_))
            .WillByDefault(Invoke(this, &TestStateInterfaceMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(ITestStateInterface::Context* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestStateInterfaceMock::handleEvent1Call( context = " << context << ") ...");
    }

    void handleEvent2Call(ITestStateInterface::Context* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestStateInterfaceMock::handleEvent2Call( context = " << context << ") ...");
    }

    void handleEvent3Call(ITestStateInterface::Context* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestStateInterfaceMock::handleEvent3Call( context = " << context << ") ...");
    }

    void handleEvent4Call(ITestStateInterface::Context* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestStateInterfaceMock::handleEvent4Call( context = " << context << ") ...");
    }
};

#endif /* TESTSTATEINTERFACEMOCK_H_ */
