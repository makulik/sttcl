/*
 * TestStateInterfaceWithArgsMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTSTATEINTERFACEWITHARGSMOCK_H_
#define TESTSTATEINTERFACEWITHARGSMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestStateInterfaceWithArgs.h"
#include "SttclStateWithArgsMock.h"
#include "SttclTestLog.h"

class SttclStateMachineWithArgsMock;

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class TestStateInterfaceWithArgsMock
: public SttclStateWithArgsMock<SttclStateMachineWithArgsMock,ITestStateInterfaceWithArgs>
{
public:
    typedef ITestStateInterfaceWithArgs StateInterface;

    virtual ~TestStateInterfaceWithArgsMock() {}

    MOCK_METHOD3(handleEvent1, void (ITestStateInterfaceWithArgs::Context* context, int arg1, const std::string& arg2));
    MOCK_METHOD2(handleEvent2, void (ITestStateInterfaceWithArgs::Context* context, double arg1));
    MOCK_METHOD1(handleEvent3, void (ITestStateInterfaceWithArgs::Context* context));
    MOCK_METHOD2(handleEvent4, void (ITestStateInterfaceWithArgs::Context* context, int arg1));

    TestStateInterfaceWithArgsMock(const std::string& stateId = "<anonymous>")
    : SttclStateWithArgsMock<SttclStateMachineWithArgsMock,ITestStateInterfaceWithArgs>(stateId)
    {
        ON_CALL(*this, handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestStateInterfaceWithArgsMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestStateInterfaceWithArgsMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestStateInterfaceWithArgsMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestStateInterfaceWithArgsMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(ITestStateInterfaceWithArgs::Context* context, int arg1, const std::string& arg2)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestStateInterfaceWithArgsMock::handleEvent1Call( context = " << context << ", arg1 = " << arg1 << ", arg2 = " << arg2 << ") ...");
    }

    void handleEvent2Call(ITestStateInterfaceWithArgs::Context* context, double arg1)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestStateInterfaceWithArgsMock::handleEvent2Call( context = " << context <<  ", arg1 = " << arg1 <<  ") ...");
    }

    void handleEvent3Call(ITestStateInterfaceWithArgs::Context* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestStateInterfaceWithArgsMock::handleEvent3Call( context = " << context << ") ...");
    }

    void handleEvent4Call(ITestStateInterfaceWithArgs::Context* context, int arg1)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestStateInterfaceWithArgsMock::handleEvent4Call( context = " << context << ", arg1 = " << arg1 << ") ...");
    }
};

#endif /* TESTSTATEINTERFACEWITHARGSMOCK_H_ */
