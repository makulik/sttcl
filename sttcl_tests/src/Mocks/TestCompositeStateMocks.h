/*
 * TestCompositeStateMocks.h
 *
 *  Created on: May 22, 2013
 *      Author: user
 */

#ifndef TESTCOMPOSITESTATEMOCKS_H_
#define TESTCOMPOSITESTATEMOCKS_H_

#include <gmock/gmock.h>
#include <StateMachine.h>
#include <CompositeState.h>

#include "SttclTestLog.h"
#include "SttclTestMockBaseClass.h"
#include "ICompositeStateClient.h"
#include "ITestStateInterfaceNoArgs.h"
#include "ITestStateInterfaceWithArgs.h"

template
    < typename CompositeStateImpl
    , typename StateMachineContext
    , typename OuterStateInterface
    , typename InnerStateInterface
    , sttcl::CompositeStateHistoryType::Values HistoryType
    >
class TestCompositeStateMock
: public SttclTestMockBaseClass
, public sttcl::CompositeState<CompositeStateImpl,StateMachineContext,InnerStateInterface,HistoryType>
, public ICompositeStateClient
    < StateMachineContext
    , sttcl::StateBase<StateMachineContext,OuterStateInterface>
    , sttcl::StateBase<CompositeStateImpl,InnerStateInterface>
    >
{
public:
    typedef TestCompositeStateMock<CompositeStateImpl,StateMachineContext,OuterStateInterface,InnerStateInterface,HistoryType> SelfClassType;
    typedef sttcl::CompositeState<CompositeStateImpl,StateMachineContext,InnerStateInterface,HistoryType> SttclCompositeStateBaseClass;
    typedef sttcl::StateMachine<CompositeStateImpl,InnerStateInterface> SttclCompsiteStateMachineBaseClass;
    typedef sttcl::StateBase<StateMachineContext,OuterStateInterface> StateBaseClass;
    //typedef SttclCompositeStateBaseClass StateBaseType;
    typedef sttcl::StateBase<CompositeStateImpl,InnerStateInterface> InnerStateBaseClass;
    typedef StateMachineContext Context;

    MOCK_METHOD1_T(entryImpl, void (Context* context));
    MOCK_METHOD1_T(exitImpl, void (Context* context));
    MOCK_METHOD1_T(startDoImpl, void (Context* context));
    MOCK_METHOD1_T(endDoImpl, void (Context* context));
    MOCK_METHOD1_T(joinDoActionImpl, void (Context* context));
    MOCK_METHOD1_T(finalizeSubStateMachinesImpl, void (bool recursive));
    MOCK_METHOD1_T(initSubStateMachinesImpl, void (bool recursive));
    MOCK_METHOD3_T(checkDirectTransitionImpl, bool (Context* context, bool& finalize, StateBaseClass*& nextState));

    MOCK_CONST_METHOD0(isReadyImpl, bool ());
    MOCK_METHOD1_T(initializeImpl, bool (bool force));
    MOCK_METHOD1_T(finalizeImpl, void (bool finalizeSubStateMachines));
    MOCK_METHOD1_T(subStateMachineCompletedImpl, void (InnerStateBaseClass* state));
    MOCK_CONST_METHOD0_T(getInitialStateImpl, InnerStateBaseClass* ());

    virtual ~TestCompositeStateMock()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "Destructor called ..."
            );
    }

    void doStateChange(Context* context, StateBaseClass* newState)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "Changing to state = " << newState << " ..."
            );
        SttclCompositeStateBaseClass::changeState(context,newState);
    }

    void setDirectTransitState(StateBaseClass* directTransitState)
    {
        directTransitState_ = directTransitState;
    }

    bool finalizeOnNextDirectTransit() const { return finalizeOnNextDirectTransit_; }
    void finalizeOnNextDirectTransit(bool value) { finalizeOnNextDirectTransit_ = value; }

    InnerStateBaseClass* initialState() const { return initialState_; }
    void initialState(InnerStateBaseClass* value) { initialState_ = value; }


protected:
    StateBaseClass* directTransitState_;
    bool finalizeOnNextDirectTransit_;
    InnerStateBaseClass* initialState_;

    TestCompositeStateMock(const std::string& id = "<anonymous>", bool loggingEnabled = false)
    : SttclTestMockBaseClass(id,loggingEnabled)
    , SttclCompositeStateBaseClass()
    , directTransitState_(0)
    , finalizeOnNextDirectTransit_(false)
    , initialState_(0)
    {
        ON_CALL(*this, entryImpl(_))
            .WillByDefault(Invoke(this, &TestCompositeStateMock::entryImplCall));
        ON_CALL(*this, exitImpl(_))
            .WillByDefault(Invoke(this, &TestCompositeStateMock::exitImplCall));
        ON_CALL(*this, startDoImpl(_))
            .WillByDefault(Invoke(this, &TestCompositeStateMock::startDoImplCall));
        ON_CALL(*this, endDoImpl(_))
            .WillByDefault(Invoke(this, &TestCompositeStateMock::endDoImplCall));
        ON_CALL(*this, joinDoActionImpl(_))
            .WillByDefault(Invoke(this, &TestCompositeStateMock::joinDoActionImplCall));
        ON_CALL(*this, finalizeSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &TestCompositeStateMock::finalizeSubStateMachinesImplCall));
        ON_CALL(*this, initSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &TestCompositeStateMock::initSubStateMachinesImplCall));
        ON_CALL(*this, checkDirectTransitionImpl(_,_,_))
            .WillByDefault(Invoke(this, &TestCompositeStateMock::checkDirectTransitionImplCall));

        ON_CALL(*this, initializeImpl(_))
            .WillByDefault(Invoke(this, &TestCompositeStateMock::initializeImplCall));
        ON_CALL(*this, finalizeImpl(_))
            .WillByDefault(Invoke(this, &TestCompositeStateMock::finalizeImplCall));
        ON_CALL(*this, subStateMachineCompletedImpl(_))
            .WillByDefault(Invoke(this, &TestCompositeStateMock::subStateMachineCompletedImplCall));
        ON_CALL(*this, getInitialStateImpl())
            .WillByDefault(Invoke(this, &TestCompositeStateMock::getInitialStateImplCall));
    }

    void entryImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "calling SttclCompositeStateBaseClass::entryImpl( context = " << context <<  ") ..."
            );
        SttclCompositeStateBaseClass::entryImpl(context);
    }

    void exitImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "calling SttclCompositeStateBaseClass::exitImpl( context = " << context <<  ") ..."
            );
        SttclCompositeStateBaseClass::exitImpl(context);
    }

    void startDoImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "calling SttclCompositeStateBaseClass::startDoImpl( context = " << context <<  ") ..."
            );
        SttclCompositeStateBaseClass::startDoImpl(context);
    }

    void endDoImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "calling SttclCompositeStateBaseClass::endDoImpl( context = " << context <<  ") ..."
            );
        SttclCompositeStateBaseClass::endDoImpl(context);
    }

    void joinDoActionImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "calling SttclCompositeStateBaseClass::joinDoActionImpl( context = " << context <<  ") ..."
            );
        SttclCompositeStateBaseClass::joinDoActionImpl(context);
    }

    void finalizeSubStateMachinesImplCall(bool recursive)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "calling SttclCompositeStateBaseClass::finalizeSubStateMachinesImpl( recursive = " << recursive <<  ") ..."
            );
        SttclCompositeStateBaseClass::finalizeSubStateMachinesImpl(recursive);
    }

    void initSubStateMachinesImplCall(bool recursive)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "calling SttclCompositeStateBaseClass::initSubStateMachinesImpl( recursive = " << recursive <<  ") ..."
            );
        SttclCompositeStateBaseClass::initSubStateMachinesImpl(recursive);
    }

    bool checkDirectTransitionImplCall(Context* context, bool& finalize, StateBaseClass*& nextState)
    {
        bool result = false;
        if(finalizeOnNextDirectTransit_)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateMock
                , "finalizing on direct transition ..."
                );
            finalize = true;
            result = true;
        }
        else if(directTransitState_)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateMock
                , "returning configured directTransitState_ = " << directTransitState_ <<  " ..."
                );
            nextState = directTransitState_;
            result = true;
        }
        else
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateMock
                , "calling SttclCompositeStateBaseClass::checkDirectTransitionImpl( context = " << context <<  ") ..."
                );
            result = SttclCompositeStateBaseClass::checkDirectTransitionImpl(context,finalize,nextState);
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateMock
                , "returning result = " << result <<  ", finalize = " << finalize << ", nextState = " << nextState << " ..."
                );
        }
        return result;
    }

    bool initializeImplCall(bool force)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "calling SttclCompsiteStateMachineBaseClass::initializeImpl( force = " << force <<  ") ..."
            );
        bool result = SttclCompsiteStateMachineBaseClass::initializeImpl(force);
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "returning result = " << result << " ..."
            );
        return result;
    }

    void finalizeImplCall(bool finalizeSubStateMachines)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "calling SttclCompsiteStateMachineBaseClass::finalizeImpl( finalizeSubStateMachines = " << finalizeSubStateMachines <<  ") ..."
            );
        SttclCompsiteStateMachineBaseClass::finalizeImpl(finalizeSubStateMachines);
    }

    void subStateMachineCompletedImplCall(InnerStateBaseClass* state)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateMock
            , "calling SttclCompsiteStateMachineBaseClass::subStateMachineCompletedImpl( state = " << state << ") ..."
            );
        SttclCompsiteStateMachineBaseClass::subStateMachineCompletedImpl(state);
    }

    InnerStateBaseClass* getInitialStateImplCall() const
    {
        InnerStateBaseClass* result = initialState();
        if(!result)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateMock
                , "calling SttclCompositeStateBaseClass::getInitialStateImpl() ..."
                );
            result = SttclCompositeStateBaseClass::getInitialStateImpl();
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateMock
                , "Using base class result = " << result
                );
        }
        else
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateMock
                , "Using mock initial state property: " << result
                );
        }
        return result;
    }
};

template
    < typename StateMachineContext
    , sttcl::CompositeStateHistoryType::Values HistoryType = sttcl::CompositeStateHistoryType::None
    >
class TestCompositeStateNoArgsMock
: public TestCompositeStateMock
      < TestCompositeStateNoArgsMock<StateMachineContext,HistoryType>
      , StateMachineContext
      , ITestStateInterfaceNoArgs<StateMachineContext>
      , ITestStateInterfaceNoArgs<TestCompositeStateNoArgsMock<StateMachineContext,HistoryType> >
      , HistoryType
      >
{
public:
    typedef TestCompositeStateMock
            < TestCompositeStateNoArgsMock<StateMachineContext,HistoryType>
            , StateMachineContext
            , ITestStateInterfaceNoArgs<StateMachineContext>
            , ITestStateInterfaceNoArgs<TestCompositeStateNoArgsMock<StateMachineContext,HistoryType> >
            , HistoryType
            > MockBaseClass;
    typedef ITestStateInterfaceNoArgs<TestCompositeStateNoArgsMock<StateMachineContext,HistoryType> > InnerStateInterface;
    typedef typename MockBaseClass::InnerStateBaseClass InnerStateBaseClass;

    TestCompositeStateNoArgsMock(const std::string& id = "<anonymous>", bool enableLogging = false)
    : MockBaseClass(id,enableLogging)
    {
        ON_CALL(*this,handleEvent1(_))
            .WillByDefault(Invoke(this, &TestCompositeStateNoArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_))
            .WillByDefault(Invoke(this, &TestCompositeStateNoArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_))
            .WillByDefault(Invoke(this, &TestCompositeStateNoArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_))
            .WillByDefault(Invoke(this, &TestCompositeStateNoArgsMock::handleEvent4Call));
    }

    virtual ~TestCompositeStateNoArgsMock() {}

    MOCK_METHOD1_T(handleEvent1, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent2, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent3, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent4, void (StateMachineContext* context));

    virtual void handleEvent1Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateNoArgsMock
            , "handleEvent1Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateNoArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent1( " <<
                  this << ") ..."
                );
            currentState->handleEvent1(this);
        }
    }

    virtual void handleEvent2Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateNoArgsMock
            , "handleEvent2Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateNoArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent2( " <<
                  this << ") ..."
                );
            currentState->handleEvent2(this);
        }
    }

    virtual void handleEvent3Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateNoArgsMock
            , "handleEvent3Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateNoArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent3( " <<
                  this << ") ..."
                );
            currentState->handleEvent3(this);
        }
    }

    virtual void handleEvent4Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateNoArgsMock
            , "handleEvent4Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateNoArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent4( " <<
                  this << ") ..."
                );
            currentState->handleEvent4(this);
        }
    }

};

template
    < typename StateMachineContext
    , sttcl::CompositeStateHistoryType::Values HistoryType = sttcl::CompositeStateHistoryType::None
    >
class TestCompositeStateWithArgsMock
: public TestCompositeStateMock
      < TestCompositeStateWithArgsMock<StateMachineContext,HistoryType>
      , StateMachineContext
      , ITestStateInterfaceWithArgs<StateMachineContext>
      , ITestStateInterfaceWithArgs<TestCompositeStateWithArgsMock<StateMachineContext,HistoryType> >
      , HistoryType
      >
{
public:
    typedef TestCompositeStateMock
            < TestCompositeStateWithArgsMock<StateMachineContext,HistoryType>
            , StateMachineContext
            , ITestStateInterfaceWithArgs<StateMachineContext>
            , ITestStateInterfaceWithArgs<TestCompositeStateWithArgsMock<StateMachineContext,HistoryType> >
            , HistoryType
            > MockBaseClass;
    typedef typename MockBaseClass::InnerStateBaseClass InnerStateBaseClass;

    TestCompositeStateWithArgsMock(const std::string& id = "<anonymous>", bool enableLogging = false)
    : MockBaseClass(id,enableLogging)
    {
        ON_CALL(*this,handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestCompositeStateWithArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestCompositeStateWithArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_))
            .WillByDefault(Invoke(this, &TestCompositeStateWithArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestCompositeStateWithArgsMock::handleEvent4Call));
    }

    virtual ~TestCompositeStateWithArgsMock() {}

    MOCK_METHOD3_T(handleEvent1, void (StateMachineContext* context, const std::string& arg1, int arg2));
    MOCK_METHOD2_T(handleEvent2, void (StateMachineContext* context, double arg1));
    MOCK_METHOD1_T(handleEvent3, void (StateMachineContext* context));
    MOCK_METHOD2_T(handleEvent4, void (StateMachineContext* context, int arg1));

    virtual void handleEvent1Call(StateMachineContext* context, const std::string& arg1, int arg2)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateWithArgsMock
            , "handleEvent1Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ", arg2 = " << arg2 <<
              ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateWithArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent1( " <<
                  this <<
                  ", arg1 = " << arg1 <<
                  ", arg2 = " << arg2 <<
                  ") ..."
                );
            currentState->handleEvent1(this,arg1,arg2);
        }
    }

    virtual void handleEvent2Call(StateMachineContext* context, double arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateWithArgsMock
            , "handleEvent2Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateWithArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent2( " <<
                  this <<
                  ", arg1 = " << arg1 <<
                  ") ..."
                );
            currentState->handleEvent2(this,arg1);
        }
    }

    virtual void handleEvent3Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateWithArgsMock
            , "handleEvent3Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateWithArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent3( " <<
                  this <<
                  ") ..."
                );
            currentState->handleEvent3(this);
        }
    }

    virtual void handleEvent4Call(StateMachineContext* context, int arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestCompositeStateWithArgsMock
            , "handleEvent4Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestCompositeStateWithArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent4( " <<
                  this <<
                  ", arg1 = " << arg1 <<
                  ") ..."
                );
            currentState->handleEvent4(this,arg1);
        }
    }

};
#endif /* TESTCOMPOSITESTATEMOCKS_H_ */
