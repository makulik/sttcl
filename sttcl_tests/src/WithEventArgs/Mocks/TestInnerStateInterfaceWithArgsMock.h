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

template<unsigned int NestingLevel = 1>
class TestInnerStateInterfaceWithArgsMock
: public SttclStateWithArgsMock<TestCompositeStateWithArgsMock<NestingLevel - 1>,ITestInnerStateInterfaceWithArgs<NestingLevel> >
{
public:
    typedef SttclStateWithArgsMock<TestCompositeStateWithArgsMock<NestingLevel - 1>,ITestInnerStateInterfaceWithArgs<NestingLevel> > SttclStateMockBase;
    typedef ITestInnerStateInterfaceWithArgs<NestingLevel> StateInterface;

    virtual ~TestInnerStateInterfaceWithArgsMock() {}

    MOCK_METHOD3_T(handleEvent1, void (TestCompositeStateWithArgsMock<NestingLevel -1>* context, int arg1, const std::string& arg2));
    MOCK_METHOD2_T(handleEvent2, void (TestCompositeStateWithArgsMock<NestingLevel -1>* context, double arg1));
    MOCK_METHOD1_T(handleEvent3, void (TestCompositeStateWithArgsMock<NestingLevel -1>* context));
    MOCK_METHOD2_T(handleEvent4, void (TestCompositeStateWithArgsMock<NestingLevel -1>* context, int arg1));

    TestInnerStateInterfaceWithArgsMock(const std::string& stateId = "<anonymous>")
    : SttclStateMockBase(stateId)
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
    void handleEvent1Call(TestCompositeStateWithArgsMock<NestingLevel -1>* context, int arg1, const std::string arg2)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceWithArgsMock::handleEvent1Call( context = " <<
              context << ", arg1 = " << arg1 << ", arg2 = " << arg2 << ") ...");
    }

    void handleEvent2Call(TestCompositeStateWithArgsMock<NestingLevel -1>* context, double arg1)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceWithArgsMock::handleEvent2Call( context = " <<
              context << ", arg1 = " << arg1 << ") ...");
    }

    void handleEvent3Call(TestCompositeStateWithArgsMock<NestingLevel -1>* context)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceWithArgsMock::handleEvent3Call( context = " <<
              context << ") ...");
    }

    void handleEvent4Call(TestCompositeStateWithArgsMock<NestingLevel -1>* context, int arg1)
    {
        STTCL_TEST_LOG
            ( SttclStateMockBase::logsEnabled()
            , "(lvl: " << NestingLevel << ") " <<
              SttclStateMockBase::id() <<
              " TestInnerStateInterfaceWithArgsMock::handleEvent4Call( context = " <<
              context << ", arg1 = " << arg1 << ") ...");
    }
};

#endif /* TESTINNERSTATEINTERFACEWITHARGSMOCK_H_ */
