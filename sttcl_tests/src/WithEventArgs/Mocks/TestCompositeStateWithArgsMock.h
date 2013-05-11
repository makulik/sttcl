/*
 * TestCompositeStateWithArgsMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTCOMPOSITESTATEWITHARGSMOCK_H_
#define TESTCOMPOSITESTATEWITHARGSMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestInnerStateInterfaceWithArgs.h"
#include "SttclCompositeStateWithArgsMock.h"
#include "SttclTestLog.h"

class SttclStateMachineWithArgsMock;

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class TestCompositeStateWithArgsMock
: public SttclCompositeStateWithArgsMock<TestCompositeStateWithArgsMock,SttclStateMachineWithArgsMock,ITestInnerStateInterfaceWithArgs>
{
public:
    typedef SttclCompositeStateWithArgsMock<TestCompositeStateWithArgsMock,SttclStateMachineWithArgsMock,ITestInnerStateInterfaceWithArgs> CompositeStateMockBase;
    virtual ~TestCompositeStateWithArgsMock()
    {
    }

    MOCK_METHOD3(handleEvent1, void (SttclStateMachineWithArgsMock* context, int arg1, const std::string& arg2));
    MOCK_METHOD2(handleEvent2, void (SttclStateMachineWithArgsMock* context, double arg1));
    MOCK_METHOD1(handleEvent3, void (SttclStateMachineWithArgsMock* context));
    MOCK_METHOD2(handleEvent4, void (SttclStateMachineWithArgsMock* context, int arg1));

    TestCompositeStateWithArgsMock(const std::string& stateId = "<anonymous>")
    : CompositeStateMockBase(stateId)
    {
        ON_CALL(*this, handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestCompositeStateWithArgsMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestCompositeStateWithArgsMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestCompositeStateWithArgsMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestCompositeStateWithArgsMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(SttclStateMachineWithArgsMock* context, int arg1, const std::string& arg2)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestCompositeStateWithArgsMock::handleEvent1Call( context = " << context << ", arg1 = " << arg1 << ", arg2 = " << arg2 << ") ...");
        InnerStateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG(logsEnabled(), id() << " TestCompositeStateWithArgsMock calling currentState->handleEvent1() ...");
            currentState->handleEvent1(this,arg1,arg2);
        }
    }

    void handleEvent2Call(SttclStateMachineWithArgsMock* context, double arg1 )
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestCompositeStateWithArgsMock::handleEvent2Call( context = " << context << ", arg1 = " << ") ...");
        InnerStateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG(logsEnabled(), id() << " TestCompositeStateWithArgsMock calling currentState->handleEvent2() ...");
            currentState->handleEvent2(this,arg1);
        }
    }

    void handleEvent3Call(SttclStateMachineWithArgsMock* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestCompositeStateWithArgsMock::handleEvent3Call( context = " << context << ") ...");
        InnerStateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG(logsEnabled(), id() << " TestCompositeStateWithArgsMock calling currentState->handleEvent3() ...");
            currentState->handleEvent3(this);
        }
    }

    void handleEvent4Call(SttclStateMachineWithArgsMock* context, int arg1)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " TestCompositeStateWithArgsMock::handleEvent4Call( context = " << context << ", arg1 = " << ") ...");
        InnerStateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG(logsEnabled(), id() << " TestCompositeStateWithArgsMock calling currentState->handleEvent4() ...");
            currentState->handleEvent4(this,arg1);
        }
    }
};

#endif /* TESTCOMPOSITESTATEWITHARGSMOCK_H_ */
