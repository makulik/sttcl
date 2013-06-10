/*
 * TestStateMachineMocks.h
 *
 *  Created on: May 21, 2013
 *      Author: user
 */

#ifndef TESTSTATEMACHINEMOCKS_H_
#define TESTSTATEMACHINEMOCKS_H_

#include <gmock/gmock.h>
#include <StateMachine.h>

#include "SttclTestLog.h"
#include "SttclTestMockBaseClass.h"
#include "IStateMachineClient.h"
#include "ITestStateInterfaceNoArgs.h"
#include "ITestStateInterfaceWithArgs.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template
    < class FinalImplType
    , class IStateInterface
    >
class TestStateMachineMock
: public sttcl::StateMachine<FinalImplType, IStateInterface>
, public IStateMachineClient<TestStateMachineMock<FinalImplType,IStateInterface>, typename sttcl::StateMachine<FinalImplType, IStateInterface>::StateBaseClass >
, public SttclTestMockBaseClass
{
public:

    typedef sttcl::StateMachine<FinalImplType, IStateInterface> SttclStateMachineBaseType;
    typedef sttcl::StateBase<FinalImplType, IStateInterface> StateBaseClass;

    // Mocking interface IStateMachineClient
    MOCK_CONST_METHOD0(isReadyImpl, bool ());
    MOCK_METHOD1(initializeImpl, bool (bool force));
    MOCK_METHOD1(finalizeImpl , void (bool finalizeSubStateMachines));
    MOCK_METHOD1_T(subStateMachineCompletedImpl, void (StateBaseClass* state));
    MOCK_CONST_METHOD0_T(getInitialStateImpl, StateBaseClass* ());

    virtual ~TestStateMachineMock()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineMock
            , "Destructor called ..."
            );
        if(autoFinalize() &&
           !SttclStateMachineBaseType::isFinalized() &&
           !SttclStateMachineBaseType::isFinalizing() &&
           !SttclStateMachineBaseType::isInitializing()
          )
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMachineMock
                , "Auto finalize, calling SttclStateMachineBaseType::finalize(true) ..."
                );
            SttclStateMachineBaseType::finalize(true);
        }
    }

    StateBaseClass* initialState() const { return initialState_; }

    template<typename StateBaseType>
    void initialState(StateBaseType* value)
    {
        initialState_ = static_cast<StateBaseClass*>(value);
    }

    bool autoFinalize() const { return autoFinalize_; }
    void autoFinalize(bool value) { autoFinalize_ = value; }

protected:
    TestStateMachineMock(const std::string& id = "<anonymous>", StateBaseClass* initialState = 0, bool enableLogging = false)
    : SttclTestMockBaseClass(id,enableLogging)
    , initialState_(initialState)
    , autoFinalize_(true)
    {
        ON_CALL(*this, isReadyImpl())
            .WillByDefault(Invoke(this, &TestStateMachineMock::isReadyImplCall));
        ON_CALL(*this, initializeImpl(_))
            .WillByDefault(Invoke(this, &TestStateMachineMock::initializeImplCall));
        ON_CALL(*this, finalizeImpl(_))
            .WillByDefault(Invoke(this, &TestStateMachineMock::finalizeImplCall));
        ON_CALL(*this, subStateMachineCompletedImpl(_))
            .WillByDefault(Invoke(this, &TestStateMachineMock::subStateMachineCompletedImplCall));
        ON_CALL(*this, getInitialStateImpl())
            .WillByDefault(Invoke(this, &TestStateMachineMock::getInitialStateImplCall));

    }

    bool isReadyImplCall() const
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineMock
            , "calling SttclStateMachineBaseType::isReadyImpl() ..."
            );
        bool result = SttclStateMachineBaseType::isReadyImpl();
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineMock
            , "returning SttclStateMachineBaseType::isReadyImpl() result = " << result
            );
        return result;
    }

    bool initializeImplCall(bool force)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineMock
            , "calling SttclStateMachineBaseType::initializeImpl(" << force << ") ..."
            );
        bool result = SttclStateMachineBaseType::initializeImpl(force);
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineMock
            , "returning SttclStateMachineBaseType::initializeImpl() result = " << result
            );
        return result;
    }

    void finalizeImplCall(bool finalizeSubStateMachines)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineMock
            , "calling SttclStateMachineBaseType::finalizeImpl(" << finalizeSubStateMachines << ") ..."
            );
        SttclStateMachineBaseType::finalizeImpl(finalizeSubStateMachines);
    }

    void subStateMachineCompletedImplCall(StateBaseClass* state)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineMock
            , "calling SttclStateMachineBaseType::subStateMachineCompletedImpl(" << state << ") ..."
            );
        SttclStateMachineBaseType::subStateMachineCompletedImpl(state);
    }

    StateBaseClass* getInitialStateImplCall() const
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineMock
            , "calling SttclStateMachineBaseType::getInitialStateImpl() ..."
            );
        StateBaseClass* result = initialState();
        if(!result)
        {
            result = SttclStateMachineBaseType::getInitialStateImpl();
            STTCL_MOCK_LOGDEBUG
                ( TestStateMachineMock
                , "Using base class result = " << result
                );
        }
        else
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMachineMock
                , "Using mock initial state property: " << result
                );
        }
        return result;
    }

    StateBaseClass* initialState_;
    bool autoFinalize_;
};

class TestStateMachineNoEventArgsMock
: public TestStateMachineMock
  < TestStateMachineNoEventArgsMock
  , ITestStateInterfaceNoArgs<TestStateMachineNoEventArgsMock>
  >
{
public:
    typedef TestStateMachineMock<TestStateMachineNoEventArgsMock, ITestStateInterfaceNoArgs<TestStateMachineNoEventArgsMock> > MockBaseClass;
    typedef typename MockBaseClass::StateBaseClass StateBaseClass;

    TestStateMachineNoEventArgsMock
        ( const std::string& id = "<anonymous>"
        , StateBaseClass* initialState = 0
        , bool enableLogging = false
        )
    : MockBaseClass(id,initialState,enableLogging)
    {
    }

    virtual ~TestStateMachineNoEventArgsMock()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineNoEventArgsMock
            , "Destructor called ..."
            );
    }

    void triggerEvent1()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineNoEventArgsMock
            , "Event1 triggered ..."
            );
        StateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMachineNoEventArgsMock
                , "calling currentState->handleEvent1("<< this << ")..."
                );
            currentState->handleEvent1(this);
        }
    }

    void triggerEvent2()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineNoEventArgsMock
            , "Event2 triggered ..."
            );
        StateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMachineNoEventArgsMock
                , "calling currentState->handleEvent2("<< this << ")..."
                );
            currentState->handleEvent2(this);
        }
    }

    void triggerEvent3()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineNoEventArgsMock
            , "Event3 triggered ..."
            );
        StateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMachineNoEventArgsMock
                , "calling currentState->handleEvent3("<< this << ")..."
                );
            currentState->handleEvent3(this);
        }
    }

    void triggerEvent4()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineNoEventArgsMock
            , "Event4 triggered ..."
            );
        StateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMachineNoEventArgsMock
                , "calling currentState->handleEvent4("<< this << ")..."
                );
            currentState->handleEvent4(this);
        }
    }
};

class TestStateMachineWithEventArgsMock
: public TestStateMachineMock<TestStateMachineWithEventArgsMock,ITestStateInterfaceWithArgs<TestStateMachineWithEventArgsMock> >
{
public:
    typedef TestStateMachineMock<TestStateMachineWithEventArgsMock, ITestStateInterfaceWithArgs<TestStateMachineWithEventArgsMock> > MockBaseClass;
    typedef typename MockBaseClass::StateBaseClass StateBaseClass;

    TestStateMachineWithEventArgsMock
        ( const std::string& id = "<anonymous>"
        , StateBaseClass* initialState = 0
        , bool enableLogging = false
        )
    : MockBaseClass(id,initialState,enableLogging)
    {
    }

    virtual ~TestStateMachineWithEventArgsMock()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineWithEventArgsMock
            , "Destructor called ..."
            );
    }

    void triggerEvent1(const std::string& arg1, int arg2)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineWithEventArgsMock
            , "Event1 triggered ..."
            );
        StateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMachineWithEventArgsMock
                , "calling currentState->handleEvent1( context = "<< this <<
                  ", arg1 = " << arg1 <<
                  ", arg2 = " << arg2 <<
                  ")..."
                );
            currentState->handleEvent1(this,arg1,arg2);
        }
    }

    void triggerEvent2(double arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineWithEventArgsMock
            , "Event2 triggered ..."
            );
        StateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMachineWithEventArgsMock
                , "calling currentState->handleEvent2( context = "<< this <<
                  ", arg1 = " << arg1 <<
                  ")..."
                );
            currentState->handleEvent2(this,arg1);
        }
    }

    void triggerEvent3()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineWithEventArgsMock
            , "Event3 triggered ..."
            );
        StateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMachineWithEventArgsMock
                , "calling currentState->handleEvent3("<< this << ")..."
                );
            currentState->handleEvent3(this);
        }
    }

    void triggerEvent4(int arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMachineWithEventArgsMock
            , "Event4 triggered ..."
            );
        StateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMachineWithEventArgsMock
                , "calling currentState->handleEvent4( context = "<< this <<
                  ", arg1 = " << arg1 <<
                  ")..."
                );
            currentState->handleEvent4(this,arg1);
        }
    }
};
#endif /* TESTSTATEMACHINEMOCKS_H_ */
