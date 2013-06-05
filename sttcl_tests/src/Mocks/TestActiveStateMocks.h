/*
 * TestActiveStateMocks.h
 *
 *  Created on: May 22, 2013
 *      Author: user
 */

#ifndef TESTACTIVESTATEMOCKS_H_
#define TESTACTIVESTATEMOCKS_H_

#include <gmock/gmock.h>
#include <StateMachine.h>
#include <ActiveState.h>

#include "SttclTestLog.h"
#include "SttclTestMockBaseClass.h"
#include "IActiveStateClient.h"
#include "ITestStateInterfaceNoArgs.h"
#include "ITestStateInterfaceWithArgs.h"

template
    < typename StateImpl
    , typename StateMachineContext
    , typename IStateInterface
    >
class TestActiveStateMock
: public SttclTestMockBaseClass
, public sttcl::ActiveState<StateImpl,StateMachineContext,IStateInterface>
, public IActiveStateClient
    < StateMachineContext
    , sttcl::StateBase<StateMachineContext,IStateInterface>
    >
{
public:
    typedef sttcl::ActiveState<StateImpl,StateMachineContext,IStateInterface> SttclStateBaseClass;
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

    MOCK_METHOD2_T(doActionImpl, void (Context* context, bool firstCall));
    MOCK_METHOD0_T(endDoActionRequestedImpl, bool());
    MOCK_METHOD0_T(exitingDoActionImpl, void ());
    MOCK_METHOD0_T(joinDoActionThreadImpl, void ());
    MOCK_METHOD0_T(unblockDoActionImpl, void ());

    virtual ~TestActiveStateMock()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "Destructor called ..."
            );
    }

    void doStateChange(Context* context, StateBaseClass* newState)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
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

    // TODO: Implementation is f***ing brittle. Using a simple semaphore and timeout would be preferred
    //       but didn't work well
    bool waitForDoActionExited(const sttcl::TimeDuration<>& checkFrequency, int retries = 1)
    {
        do
        {
            if(doActionExited_)
            {
                return true;
            }
            sttcl::internal::SttclThread<>::sleep(checkFrequency);
            --retries;
        } while(retries > 0);
        return false;
    }

protected:
    StateBaseClass* directTransitState_;
    bool finalizeOnNextDirectTransit_;
    volatile bool doActionExited_;

    TestActiveStateMock
        ( bool runDoActionOnce = false
        , sttcl::TimeDuration<> doFrequency = sttcl::TimeDuration<>(0,0,0,10)
        , const std::string& id = "<anonymous>"
        , bool loggingEnabled = false
        )
    : SttclTestMockBaseClass(id,loggingEnabled)
    , SttclStateBaseClass(&TestActiveStateMock::doActionImpl,runDoActionOnce,doFrequency)
    , directTransitState_(0)
    , finalizeOnNextDirectTransit_(false)
    , doActionExited_(false)
    {
        ON_CALL(*this, entryImpl(_))
            .WillByDefault(Invoke(this, &TestActiveStateMock::entryImplCall));
        ON_CALL(*this, exitImpl(_))
            .WillByDefault(Invoke(this, &TestActiveStateMock::exitImplCall));
        ON_CALL(*this, startDoImpl(_))
            .WillByDefault(Invoke(this, &TestActiveStateMock::startDoImplCall));
        ON_CALL(*this, endDoImpl(_))
            .WillByDefault(Invoke(this, &TestActiveStateMock::endDoImplCall));
        ON_CALL(*this, joinDoActionImpl(_))
            .WillByDefault(Invoke(this, &TestActiveStateMock::joinDoActionImplCall));
        ON_CALL(*this, finalizeSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &TestActiveStateMock::finalizeSubStateMachinesImplCall));
        ON_CALL(*this, initSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &TestActiveStateMock::initSubStateMachinesImplCall));
        ON_CALL(*this, checkDirectTransitionImpl(_,_,_))
            .WillByDefault(Invoke(this, &TestActiveStateMock::checkDirectTransitionImplCall));

        ON_CALL(*this, doActionImpl(_,_))
            .WillByDefault(Invoke(this, &TestActiveStateMock::doActionImplCall));
        ON_CALL(*this, endDoActionRequestedImpl())
            .WillByDefault(Invoke(this, &TestActiveStateMock::endDoActionRequestedImplCall));
        ON_CALL(*this, exitingDoActionImpl())
            .WillByDefault(Invoke(this, &TestActiveStateMock::exitingDoActionImplCall));
        ON_CALL(*this, joinDoActionThreadImpl())
            .WillByDefault(Invoke(this, &TestActiveStateMock::joinDoActionThreadImplCall));
        ON_CALL(*this, unblockDoActionImpl())
            .WillByDefault(Invoke(this, &TestActiveStateMock::unblockDoActionImplCall));
    }

    void entryImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "calling SttclStateBaseClass::entryImpl( context = " << context <<  ") ..."
            );
        SttclStateBaseClass::entryImpl(context);
    }

    void exitImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "calling SttclStateBaseClass::exitImpl( context = " << context <<  ") ..."
            );
        SttclStateBaseClass::exitImpl(context);
    }

    void startDoImplCall(Context* context)
    {
        doActionExited_ = false;
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "calling SttclStateBaseClass::startDoImpl( context = " << context <<  ") ..."
            );
        SttclStateBaseClass::startDoImpl(context);
    }

    void endDoImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "calling SttclStateBaseClass::endDoImpl( context = " << context <<  ") ..."
            );
        SttclStateBaseClass::endDoImpl(context);
    }

    void joinDoActionImplCall(Context* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "calling SttclStateBaseClass::joinDoActionImpl( context = " << context <<  ") ..."
            );
        SttclStateBaseClass::joinDoActionImpl(context);
    }

    void finalizeSubStateMachinesImplCall(bool recursive)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "calling SttclStateBaseClass::finalizeSubStateMachinesImpl( recursive = " << recursive <<  ") ..."
            );
        SttclStateBaseClass::finalizeSubStateMachinesImpl(recursive);
    }

    void initSubStateMachinesImplCall(bool recursive)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
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
                ( TestActiveStateMock
                , "finalizing on direct transition ..."
                );
            finalize = true;
            result = true;
        }
        else if(directTransitState_)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestActiveStateMock
                , "returning configured directTransitState_ = " << directTransitState_ <<  " ..."
                );
            nextState = directTransitState_;
            result = true;
        }
        else
        {
            STTCL_MOCK_LOGDEBUG
                ( TestActiveStateMock
                , "calling SttclStateBaseClass::checkDirectTransitionImpl( context = " << context <<  ") ..."
                );
            result = SttclStateBaseClass::checkDirectTransitionImpl(context,finalize,nextState);
            STTCL_MOCK_LOGDEBUG
                ( TestActiveStateMock
                , "returning result = " << result <<  ", finalize = " << finalize << ", nextState = " << nextState << " ..."
                );
        }
        return result;
    }

    void doActionImplCall(Context* context, bool firstCall)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "doActionImplCall( context = " << context << ", firstCall = " << firstCall << ") called"
            );
    }

    bool endDoActionRequestedImplCall()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "calling SttclStateBaseClass::endDoActionRequestedImpl() ..."
            );
        bool result = SttclStateBaseClass::endDoActionRequestedImpl();
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "returning result = " << result << " ..."
            );
        return result;
    }

    void exitingDoActionImplCall()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "calling SttclStateBaseClass::exitingDoActionImpl() ..."
            );
        doActionExited_ = true;
        SttclStateBaseClass::exitingDoActionImpl();
    }

    void joinDoActionThreadImplCall()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "calling SttclStateBaseClass::joinDoActionThreadImpl() ..."
            );
        SttclStateBaseClass::joinDoActionThreadImpl();
    }

    void unblockDoActionImplCall()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateMock
            , "calling SttclStateBaseClass::unblockDoActionImpl() ..."
            );
        SttclStateBaseClass::unblockDoActionImpl();
    }

};

template
    < typename StateMachineContext
    >
class TestActiveStateNoArgsMock
: public TestActiveStateMock<TestActiveStateNoArgsMock<StateMachineContext>, StateMachineContext, ITestStateInterfaceNoArgs<StateMachineContext> >
{
public:
    typedef TestActiveStateMock<TestActiveStateNoArgsMock<StateMachineContext>, StateMachineContext, ITestStateInterfaceNoArgs<StateMachineContext> > MockBaseClass;

    TestActiveStateNoArgsMock
    ( bool runDoActionOnce = false
    , sttcl::TimeDuration<> doFrequency = sttcl::TimeDuration<>(0,0,0,10)
    , const std::string& id = "<anonymous>"
    , bool loggingEnabled = false
    )
    : MockBaseClass(runDoActionOnce,doFrequency,id,loggingEnabled)
    {
        ON_CALL(*this,handleEvent1(_))
            .WillByDefault(Invoke(this, &TestActiveStateNoArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_))
            .WillByDefault(Invoke(this, &TestActiveStateNoArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_))
            .WillByDefault(Invoke(this, &TestActiveStateNoArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_))
            .WillByDefault(Invoke(this, &TestActiveStateNoArgsMock::handleEvent4Call));
    }

    virtual ~TestActiveStateNoArgsMock() {}

    MOCK_METHOD1_T(handleEvent1, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent2, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent3, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent4, void (StateMachineContext* context));

protected:

    virtual void handleEvent1Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateNoArgsMock
            , "handleEvent1Call( context = " << context <<  ") called ..."
            );
    }

    virtual void handleEvent2Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateNoArgsMock
            , "handleEvent2Call( context = " << context <<  ") called ..."
            );
    }

    virtual void handleEvent3Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateNoArgsMock
            , "handleEvent3Call( context = " << context <<  ") called ..."
            );
    }

    virtual void handleEvent4Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateNoArgsMock
            , "handleEvent2Call( context = " << context <<  ") called ..."
            );
    }

};

template
    < typename StateMachineContext
    >
class TestActiveStateWithArgsMock
: public TestActiveStateMock<TestActiveStateWithArgsMock<StateMachineContext>, StateMachineContext, ITestStateInterfaceWithArgs<StateMachineContext> >
{
public:
    typedef TestActiveStateMock<TestActiveStateWithArgsMock<StateMachineContext>, StateMachineContext, ITestStateInterfaceWithArgs<StateMachineContext> > MockBaseClass;

    TestActiveStateWithArgsMock
    ( bool runDoActionOnce = false
    , sttcl::TimeDuration<> doFrequency = sttcl::TimeDuration<>(0,0,0,10)
    , const std::string& id = "<anonymous>"
    , bool loggingEnabled = false
    )
    : MockBaseClass(runDoActionOnce,doFrequency,id,loggingEnabled)
    {
        ON_CALL(*this,handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestActiveStateWithArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestActiveStateWithArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_))
            .WillByDefault(Invoke(this, &TestActiveStateWithArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestActiveStateWithArgsMock::handleEvent4Call));
    }

    virtual ~TestActiveStateWithArgsMock() {}

    MOCK_METHOD3_T(handleEvent1, void (StateMachineContext* context, const std::string& arg1, int arg2));
    MOCK_METHOD2_T(handleEvent2, void (StateMachineContext* context, double arg1));
    MOCK_METHOD1_T(handleEvent3, void (StateMachineContext* context));
    MOCK_METHOD2_T(handleEvent4, void (StateMachineContext* context, int arg1));

protected:

    virtual void handleEvent1Call(StateMachineContext* context, const std::string& arg1, int arg2)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateWithArgsMock
            , "handleEvent1Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ", arg2 = " << arg2 <<
              ") called ..."
            );
    }

    virtual void handleEvent2Call(StateMachineContext* context, double arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateWithArgsMock
            , "handleEvent2Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ") called ..."
            );
    }

    virtual void handleEvent3Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateWithArgsMock
            , "handleEvent3Call( context = " << context <<  ") called ..."
            );
    }

    virtual void handleEvent4Call(StateMachineContext* context, int arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestActiveStateWithArgsMock
            , "handleEvent2Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ") called ..."
            );
    }

};
#endif /* TESTACTIVESTATEMOCKS_H_ */
