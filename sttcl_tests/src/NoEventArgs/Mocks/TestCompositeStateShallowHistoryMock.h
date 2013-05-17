/*
 * TestCompositeStateShallowHistoryMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTCOMPOSITESTATESHALLOWHISTORYMOCK_H_
#define TESTCOMPOSITESTATESHALLOWHISTORYMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestInnerStateInterfaceShallowHistory.h"
#include "SttclCompositeStateMock.h"
#include "SttclTestLog.h"

class SttclStateMachineMock;

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template<unsigned int NestingLevel = 0>
class TestCompositeStateShallowHistoryMock
: public SttclCompositeStateMock<TestCompositeStateShallowHistoryMock<NestingLevel>,SttclStateMachineMock,ITestInnerStateInterfaceShallowHistory<NestingLevel + 1>, NestingLevel, sttcl::CompositeStateHistoryType::Shallow>
{
public:
    typedef SttclCompositeStateMock<TestCompositeStateShallowHistoryMock<NestingLevel>,SttclStateMachineMock,ITestInnerStateInterfaceShallowHistory<NestingLevel + 1>, NestingLevel, sttcl::CompositeStateHistoryType::Shallow> CompositeStateMockBase;
    typedef typename CompositeStateMockBase::InnerStateBaseClass InnerStateBaseClass;

    virtual ~TestCompositeStateShallowHistoryMock()
    {
    }

    MOCK_METHOD1(handleEvent1, void (SttclStateMachineMock* context));
    MOCK_METHOD1(handleEvent2, void (SttclStateMachineMock* context));
    MOCK_METHOD1(handleEvent3, void (SttclStateMachineMock* context));
    MOCK_METHOD1(handleEvent4, void (SttclStateMachineMock* context));

    TestCompositeStateShallowHistoryMock(const std::string& stateId = "<anonymous>")
    : CompositeStateMockBase(stateId)
    {
        ON_CALL(*this, handleEvent1(_))
            .WillByDefault(Invoke(this, &TestCompositeStateShallowHistoryMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_))
            .WillByDefault(Invoke(this, &TestCompositeStateShallowHistoryMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestCompositeStateShallowHistoryMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_))
            .WillByDefault(Invoke(this, &TestCompositeStateShallowHistoryMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(SttclStateMachineMock* context)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , CompositeStateMockBase::id() <<
              " TestCompositeStateShallowHistoryMock::handleEvent1Call( context = " <<
              context << ") ...");
        InnerStateBaseClass* currentState = CompositeStateMockBase::getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG
                ( CompositeStateMockBase::logsEnabled()
                , CompositeStateMockBase::id() <<
                  " TestCompositeStateShallowHistoryMock calling currentState->handleEvent1() ...");
            currentState->handleEvent1(this);
        }
    }

    void handleEvent2Call(SttclStateMachineMock* context)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , CompositeStateMockBase::id() <<
              " TestCompositeStateShallowHistoryMock::handleEvent2Call( context = " <<
              context << ") ...");
        InnerStateBaseClass* currentState = CompositeStateMockBase::getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG
                ( CompositeStateMockBase::logsEnabled()
                , CompositeStateMockBase::id() <<
                  " TestCompositeStateShallo-wHistoryMock calling currentState->handleEvent2() ...");
            currentState->handleEvent2(this);
        }
    }

    void handleEvent3Call(SttclStateMachineMock* context)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , CompositeStateMockBase::id() <<
              " TestCompositeStateShallowHistoryMock::handleEvent3Call( context = " <<
              context << ") ...");
        InnerStateBaseClass* currentState = CompositeStateMockBase::getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG
                ( CompositeStateMockBase::logsEnabled()
                , CompositeStateMockBase::id() <<
                  " TestCompositeStateShallowHistoryMock calling currentState->handleEvent3() ...");
            currentState->handleEvent3(this);
        }
    }

    void handleEvent4Call(SttclStateMachineMock* context)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , CompositeStateMockBase::id() <<
              " TestCompositeStateShallowHistoryMock::handleEvent4Call( context = " <<
              context << ") ...");
        InnerStateBaseClass* currentState = CompositeStateMockBase::getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG
                ( CompositeStateMockBase::logsEnabled()
                , CompositeStateMockBase::id() <<
                  " TestCompositeStateShallowHistoryMock calling currentState->handleEvent4() ...");
            currentState->handleEvent4(this);
        }
    }
};

#endif /* TESTCOMPOSITESTATEMOCK_H_ */
