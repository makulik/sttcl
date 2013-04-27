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

class TestInnerStateInterfaceMock
: public SttclStateMock<TestCompositeStateMock,ITestInnerStateInterface>
{
public:
    typedef ITestInnerStateInterface StateInterface;

    virtual ~TestInnerStateInterfaceMock() {}

    MOCK_METHOD1(handleEvent1, void (TestCompositeStateMock* context));
    MOCK_METHOD1(handleEvent2, void (TestCompositeStateMock* context));
    MOCK_METHOD1(handleEvent3, void (TestCompositeStateMock* context));
    MOCK_METHOD1(handleEvent4, void (TestCompositeStateMock* context));

    TestInnerStateInterfaceMock(const std::string& stateId = "<anonymous>")
    : SttclStateMock<TestCompositeStateMock,ITestInnerStateInterface>(stateId)
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
    void handleEvent1Call(TestCompositeStateMock* context)
    {
        if(logsEnabled())
        {
            STTCL_TEST_LOG(id() << " TestInnerStateInterfaceMock::handleEvent1Call( context = " << context << ") ...");
        }
    }

    void handleEvent2Call(TestCompositeStateMock* context)
    {
        if(logsEnabled())
        {
            STTCL_TEST_LOG(id() << " TestInnerStateInterfaceMock::handleEvent2Call( context = " << context << ") ...");
        }
    }

    void handleEvent3Call(TestCompositeStateMock* context)
    {
        if(logsEnabled())
        {
            STTCL_TEST_LOG(id() << " TestInnerStateInterfaceMock::handleEvent3Call( context = " << context << ") ...");
        }
    }

    void handleEvent4Call(TestCompositeStateMock* context)
    {
        if(logsEnabled())
        {
            STTCL_TEST_LOG(id() << " TestInnerStateInterfaceMock::handleEvent4Call( context = " << context << ") ...");
        }
    }
};

#endif /* TESTINNERSTATEINTERFACEMOCK_H_ */
