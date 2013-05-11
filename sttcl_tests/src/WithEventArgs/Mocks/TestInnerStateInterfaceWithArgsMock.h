/*
 * TestInnerStateInterfaceWithArgsMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTINNERSTATEINTERFACEWITHARGSMOCK_H_
#define TESTINNERSTATEINTERFACEWITHARGSMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestInnerStateInterfaceWithArgs.h"
#include "IStateMachineWithArgsHooks.h"
#include "IStateWithArgsHooks.h"
#include "SttclStateWithArgsMock.h"
#include "SttclTestLog.h"

#include "TestCompositeStateWithArgsMock.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class TestInnerStateInterfaceWithArgsMock
: public SttclStateWithArgsMock<TestCompositeStateWithArgsMock,ITestInnerStateInterfaceWithArgs>
{
public:
    typedef ITestInnerStateInterfaceWithArgs StateInterface;

    virtual ~TestInnerStateInterfaceWithArgsMock() {}

    MOCK_METHOD3(handleEvent1, void (TestCompositeStateWithArgsMock* context, int arg1, const std::string& arg2));
    MOCK_METHOD2(handleEvent2, void (TestCompositeStateWithArgsMock* context, double arg1));
    MOCK_METHOD1(handleEvent3, void (TestCompositeStateWithArgsMock* context));
    MOCK_METHOD2(handleEvent4, void (TestCompositeStateWithArgsMock* context, int arg1));

    TestInnerStateInterfaceWithArgsMock(const std::string& stateId = "<anonymous>")
    : SttclStateWithArgsMock<TestCompositeStateWithArgsMock,ITestInnerStateInterfaceWithArgs>(stateId)
    {
        ON_CALL(*this, handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceWithArgsMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceWithArgsMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceWithArgsMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestInnerStateInterfaceWithArgsMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(TestCompositeStateWithArgsMock* context, int arg1, const std::string arg2)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestInnerStateInterfaceWithArgsMock::handleEvent1Call( context = " << context << ", arg1 = " << arg1 << ", arg2 = " << arg2 << ") ...");
    }

    void handleEvent2Call(TestCompositeStateWithArgsMock* context, double arg1)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestInnerStateInterfaceWithArgsMock::handleEvent2Call( context = " << context << ", arg1 = " << arg1 << ") ...");
    }

    void handleEvent3Call(TestCompositeStateWithArgsMock* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestInnerStateInterfaceWithArgsMock::handleEvent3Call( context = " << context << ") ...");
    }

    void handleEvent4Call(TestCompositeStateWithArgsMock* context, int arg1)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestInnerStateInterfaceWithArgsMock::handleEvent4Call( context = " << context << ", arg1 = " << arg1 << ") ...");
    }
};

#endif /* TESTINNERSTATEINTERFACEWITHARGSMOCK_H_ */
