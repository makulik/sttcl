/*
 * TestCompositeStateDeepHistoryMock.h
 *
 *  Created on: Apr 25, 2013
 *      Author: user
 */

#ifndef TESTCOMPOSITESTATEDEEPHISTORYMOCK_H_
#define TESTCOMPOSITESTATEDEEPHISTORYMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestInnerStateInterfaceDeepHistory.h"
#include "SttclCompositeStateMock.h"
#include "SttclTestLog.h"

class SttclStateMachineMock;

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template<unsigned int NestingLevel = 0>
class TestCompositeStateDeepHistoryMock
: public SttclCompositeStateMock<TestCompositeStateDeepHistoryMock<NestingLevel>,SttclStateMachineMock,ITestInnerStateInterfaceDeepHistory<NestingLevel + 1>, NestingLevel, sttcl::CompositeStateHistoryType::Deep>
{
public:
    typedef SttclCompositeStateMock<TestCompositeStateDeepHistoryMock<NestingLevel>,SttclStateMachineMock,ITestInnerStateInterfaceDeepHistory<NestingLevel + 1>, NestingLevel, sttcl::CompositeStateHistoryType::Deep> CompositeStateMockBase;
    typedef typename CompositeStateMockBase::InnerStateBaseClass InnerStateBaseClass;

    virtual ~TestCompositeStateDeepHistoryMock()
    {
    }

    MOCK_METHOD1(handleEvent1, void (SttclStateMachineMock* context));
    MOCK_METHOD1(handleEvent2, void (SttclStateMachineMock* context));
    MOCK_METHOD1(handleEvent3, void (SttclStateMachineMock* context));
    MOCK_METHOD1(handleEvent4, void (SttclStateMachineMock* context));

    TestCompositeStateDeepHistoryMock(const std::string& stateId = "<anonymous>")
    : CompositeStateMockBase(stateId)
    {
        ON_CALL(*this, handleEvent1(_))
            .WillByDefault(Invoke(this, &TestCompositeStateDeepHistoryMock::handleEvent1Call));
        ON_CALL(*this, handleEvent2(_))
            .WillByDefault(Invoke(this, &TestCompositeStateDeepHistoryMock::handleEvent2Call));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &TestCompositeStateDeepHistoryMock::handleEvent3Call));
        ON_CALL(*this, handleEvent4(_))
            .WillByDefault(Invoke(this, &TestCompositeStateDeepHistoryMock::handleEvent4Call));

    }

protected:
    void handleEvent1Call(SttclStateMachineMock* context)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , CompositeStateMockBase::id() <<
              " TestCompositeStateDeepHistoryMock::handleEvent1Call( context = " <<
              context << ") ...");
        InnerStateBaseClass* currentState = CompositeStateMockBase::getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG
                ( CompositeStateMockBase::logsEnabled()
                , CompositeStateMockBase::id() <<
                  " TestCompositeStateDeepHistoryMock calling currentState->handleEvent1() ...");
            currentState->handleEvent1(this);
        }
    }

    void handleEvent2Call(SttclStateMachineMock* context)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , CompositeStateMockBase::id() <<
              " TestCompositeStateDeepHistoryMock::handleEvent2Call( context = " <<
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
              " TestCompositeStateDeepHistoryMock::handleEvent3Call( context = " <<
              context << ") ...");
        InnerStateBaseClass* currentState = CompositeStateMockBase::getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG
                ( CompositeStateMockBase::logsEnabled()
                , CompositeStateMockBase::id() <<
                  " TestCompositeStateDeepHistoryMock calling currentState->handleEvent3() ...");
            currentState->handleEvent3(this);
        }
    }

    void handleEvent4Call(SttclStateMachineMock* context)
    {
        STTCL_TEST_LOG
            ( CompositeStateMockBase::logsEnabled()
            , CompositeStateMockBase::id() <<
              " TestCompositeStateDeepHistoryMock::handleEvent4Call( context = " <<
              context << ") ...");
        InnerStateBaseClass* currentState = CompositeStateMockBase::getState();
        if(currentState != NULL)
        {
            STTCL_TEST_LOG
                ( CompositeStateMockBase::logsEnabled()
                , CompositeStateMockBase::id() <<
                  " TestCompositeStateDeepHistoryMock calling currentState->handleEvent4() ...");
            currentState->handleEvent4(this);
        }
    }
};

#endif /* TESTCOMPOSITESTATEDEEPHISTORYMOCK_H_ */
