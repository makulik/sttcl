/*
 * TestStateMocks.h
 *
 *  Created on: May 22, 2013
 *      Author: user
 */

#ifndef TESTSTATEMOCKS_H_
#define TESTSTATEMOCKS_H_

#include <gmock/gmock.h>
#include <StateMachine.h>

#include "SttclTestLog.h"
#include "SttclTestMockBaseClass.h"
#include "ISimpleStateClient.h"
#include "ITestStateInterfaceNoArgs.h"
#include "ITestStateInterfaceWithArgs.h"

template
    < typename StateImpl
    , typename StateMachineContext
    , typename IStateInterface
    >
class TestStateMock
: public SttclTestMockBaseClass
, public sttcl::State<StateImpl,StateMachineContext,IStateInterface>
, public ISimpleStateClient
    < StateMachineContext
    , sttcl::StateBase<StateMachineContext,IStateInterface>
    >
{
public:
    typedef sttcl::State<StateImpl,StateMachineContext,IStateInterface> SttclStateBaseClass;
    typedef sttcl::StateBase<StateMachineContext,IStateInterface> StateBaseClass;
    typedef SttclStateBaseClass StateBaseType;
    typedef StateMachineContext Context;

    MOCK_METHOD1_T(entryImpl, void (Context* context));
    MOCK_METHOD1_T(exitImpl, void (Context* context));
    MOCK_METHOD1_T(startDoImpl, void (Context* context));
    MOCK_METHOD1_T(endDoImpl, void (Context* context));
    MOCK_METHOD1_T(joinDoActionImpl, void (Context* context));
    MOCK_METHOD1_T(finalizeSubStateMachinesImpl, void (bool recursive));
    MOCK_METHOD1_T(initSubStateMachinesImpl, void (bool recursive));
    MOCK_METHOD3_T(checkDirectTransitionImpl, bool (Context* context, bool& finalize, StateBaseClass*& nextState));

    virtual ~TestStateMock()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMock
            , "Destructor called ..."
            );
    }

    void doStateChange(Context* context, StateBaseClass* newState)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMock
            , "Changing to state = " << newState << " ..."
            );
        SttclStateBaseClass::changeState(context,newState);
    }

    void setDirectTransitState(StateBaseClass* directTransitState)
    {
        directTransitState_ = directTransitState;
    }

    bool finalizeOnNextDirectTransit() const { return finalizeOnNextDirectTransit_; }
    void finalizeOnNextDirectTransit(bool value) { finalizeOnNextDirectTransit_ = value; }

protected:
    StateBaseClass* directTransitState_;
    bool finalizeOnNextDirectTransit_;

    TestStateMock(const std::string& id = "<anonymous>", bool loggingEnabled = false)
    : SttclTestMockBaseClass(id,loggingEnabled)
    , SttclStateBaseClass()
    , directTransitState_(0)
    , finalizeOnNextDirectTransit_(false)
    {
        ON_CALL(*this, entryImpl(_))
            .WillByDefault(Invoke(this, &TestStateMock::entryImplCall));
        ON_CALL(*this, exitImpl(_))
            .WillByDefault(Invoke(this, &TestStateMock::exitImplCall));
        ON_CALL(*this, startDoImpl(_))
            .WillByDefault(Invoke(this, &TestStateMock::startDoImplCall));
        ON_CALL(*this, endDoImpl(_))
            .WillByDefault(Invoke(this, &TestStateMock::endDoImplCall));
        ON_CALL(*this, joinDoActionImpl(_))
            .WillByDefault(Invoke(this, &TestStateMock::joinDoActionImplCall));
        ON_CALL(*this, finalizeSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &TestStateMock::finalizeSubStateMachinesImplCall));
        ON_CALL(*this, initSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &TestStateMock::initSubStateMachinesImplCall));
        ON_CALL(*this, checkDirectTransitionImpl(_,_,_))
            .WillByDefault(Invoke(this, &TestStateMock::checkDirectTransitionImplCall));
    }

    void entryImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMock
            , "calling SttclStateBaseClass::entryImpl( context = " << context <<  ") ..."
            );
        SttclStateBaseClass::entryImpl(context);
    }

    void exitImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMock
            , "calling SttclStateBaseClass::exitImpl( context = " << context <<  ") ..."
            );
        SttclStateBaseClass::exitImpl(context);
    }

    void startDoImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMock
            , "calling SttclStateBaseClass::startDoImpl( context = " << context <<  ") ..."
            );
        SttclStateBaseClass::startDoImpl(context);
    }

    void endDoImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMock
            , "calling SttclStateBaseClass::endDoImpl( context = " << context <<  ") ..."
            );
        SttclStateBaseClass::endDoImpl(context);
    }

    void joinDoActionImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMock
            , "calling SttclStateBaseClass::joinDoActionImpl( context = " << context <<  ") ..."
            );
        SttclStateBaseClass::joinDoActionImpl(context);
    }

    void finalizeSubStateMachinesImplCall(bool recursive)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMock
            , "calling SttclStateBaseClass::finalizeSubStateMachinesImpl( recursive = " << recursive <<  ") ..."
            );
        SttclStateBaseClass::finalizeSubStateMachinesImpl(recursive);
    }

    void initSubStateMachinesImplCall(bool recursive)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestStateMock
            , "calling SttclStateBaseClass::initSubStateMachinesImpl( recursive = " << recursive <<  ") ..."
            );
        SttclStateBaseClass::initSubStateMachinesImpl(recursive);
    }

    bool checkDirectTransitionImplCall(Context* context, bool& finalize, StateBaseClass*& nextState)
    {
        bool result = false;
        if(finalizeOnNextDirectTransit_)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMock
                , "finalizing on direct transition ..."
                );
            finalize = true;
            result = true;
        }
        else if(directTransitState_)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMock
                , "returning configured directTransitState_ = " << directTransitState_ <<  " ..."
                );
            nextState = directTransitState_;
            result = true;
        }
        else
        {
            STTCL_MOCK_LOGDEBUG
                ( TestStateMock
                , "calling SttclStateBaseClass::checkDirectTransitionImpl( context = " << context <<  ") ..."
                );
            result = SttclStateBaseClass::checkDirectTransitionImpl(context,finalize,nextState);
            STTCL_MOCK_LOGDEBUG
                ( TestStateMock
                , "returning result = " << result <<  ", finalize = " << finalize << ", nextState = " << nextState << " ..."
                );
        }
        return result;
    }
};

template
    < typename StateMachineContext
    >
class TestSimpleStateNoArgsMock
: public TestStateMock<TestSimpleStateNoArgsMock<StateMachineContext>, StateMachineContext, ITestStateInterfaceNoArgs<StateMachineContext> >
{
public:
    typedef TestStateMock<TestSimpleStateNoArgsMock<StateMachineContext>, StateMachineContext, ITestStateInterfaceNoArgs<StateMachineContext> > MockBaseClass;

    TestSimpleStateNoArgsMock(const std::string& id = "<anonymous>", bool enableLogging = false)
    : MockBaseClass(id,enableLogging)
    {
        ON_CALL(*this,handleEvent1(_))
            .WillByDefault(Invoke(this, &TestSimpleStateNoArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_))
            .WillByDefault(Invoke(this, &TestSimpleStateNoArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_))
            .WillByDefault(Invoke(this, &TestSimpleStateNoArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_))
            .WillByDefault(Invoke(this, &TestSimpleStateNoArgsMock::handleEvent4Call));
    }

    virtual ~TestSimpleStateNoArgsMock() {}

    MOCK_METHOD1_T(handleEvent1, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent2, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent3, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent4, void (StateMachineContext* context));

protected:

    virtual void handleEvent1Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestSimpleStateNoArgsMock
            , "handleEvent1Call( context = " << context <<  ") called ..."
            );
    }

    virtual void handleEvent2Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestSimpleStateNoArgsMock
            , "handleEvent2Call( context = " << context <<  ") called ..."
            );
    }

    virtual void handleEvent3Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestSimpleStateNoArgsMock
            , "handleEvent3Call( context = " << context <<  ") called ..."
            );
    }

    virtual void handleEvent4Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestSimpleStateNoArgsMock
            , "handleEvent2Call( context = " << context <<  ") called ..."
            );
    }

};

template
    < typename StateMachineContext
    >
class TestSimpleStateWithArgsMock
: public TestStateMock<TestSimpleStateWithArgsMock<StateMachineContext>, StateMachineContext, ITestStateInterfaceWithArgs<StateMachineContext> >
{
public:
    typedef TestStateMock<TestSimpleStateWithArgsMock<StateMachineContext>, StateMachineContext, ITestStateInterfaceWithArgs<StateMachineContext> > MockBaseClass;

    TestSimpleStateWithArgsMock(const std::string& id = "<anonymous>", bool enableLogging = false)
    : MockBaseClass(id,enableLogging)
    {
        ON_CALL(*this,handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestSimpleStateWithArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestSimpleStateWithArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_))
            .WillByDefault(Invoke(this, &TestSimpleStateWithArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestSimpleStateWithArgsMock::handleEvent4Call));
    }

    virtual ~TestSimpleStateWithArgsMock() {}

    MOCK_METHOD3_T(handleEvent1, void (StateMachineContext* context, const std::string& arg1, int arg2));
    MOCK_METHOD2_T(handleEvent2, void (StateMachineContext* context, double arg1));
    MOCK_METHOD1_T(handleEvent3, void (StateMachineContext* context));
    MOCK_METHOD2_T(handleEvent4, void (StateMachineContext* context, int arg1));

protected:

    virtual void handleEvent1Call(StateMachineContext* context, const std::string& arg1, int arg2)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestSimpleStateWithArgsMock
            , "handleEvent1Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ", arg2 = " << arg2 <<
              ") called ..."
            );
    }

    virtual void handleEvent2Call(StateMachineContext* context, double arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestSimpleStateWithArgsMock
            , "handleEvent2Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ") called ..."
            );
    }

    virtual void handleEvent3Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestSimpleStateWithArgsMock
            , "handleEvent3Call( context = " << context <<  ") called ..."
            );
    }

    virtual void handleEvent4Call(StateMachineContext* context, int arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestSimpleStateWithArgsMock
            , "handleEvent2Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ") called ..."
            );
    }

};
#endif /* TESTSTATEMOCKS_H_ */
