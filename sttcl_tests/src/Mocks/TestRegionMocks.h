/*
 * TestRegionMocks.h
 *
 *  Created on: May 22, 2013
 *      Author: user
 */

#ifndef TESTCOMPOSITESTATEMOCKS_H_
#define TESTCOMPOSITESTATEMOCKS_H_

#include <gmock/gmock.h>
#include <StateMachine.h>
#include <Region.h>

#include "SttclTestLog.h"
#include "SttclTestMockBaseClass.h"
#include "IRegionClient.h"
#include "ITestStateInterfaceNoArgs.h"
#include "ITestStateInterfaceWithArgs.h"

template
    < typename RegionImpl
    , typename RegionContainer
    , typename OuterStateInterface
    , typename InnerStateInterface
    , sttcl::RegionHistoryType::Values HistoryType
    >
class TestRegionMock
: public SttclTestMockBaseClass
, public sttcl::Region<RegionImpl,RegionContainer,InnerStateInterface,HistoryType>
, public IRegionClient
    < RegionContainer
    , sttcl::StateBase<RegionContainer,OuterStateInterface>
    , sttcl::StateBase<RegionImpl,InnerStateInterface>
    >
{
public:
    typedef TestRegionMock<RegionImpl,RegionContainer,OuterStateInterface,InnerStateInterface,HistoryType> SelfClassType;
    typedef sttcl::Region<RegionImpl,RegionContainer,InnerStateInterface,HistoryType> SttclRegionBaseClass;
    typedef sttcl::StateMachine<RegionImpl,InnerStateInterface> SttclCompsiteStateMachineBaseClass;
    typedef sttcl::StateBase<RegionContainer,OuterStateInterface> StateBaseClass;
    //typedef SttclRegionBaseClass StateBaseType;
    typedef sttcl::StateBase<RegionImpl,InnerStateInterface> InnerStateBaseClass;
    typedef RegionContainer Context;

    MOCK_CONST_METHOD0_T(getInitialStateImpl, InnerStateClass* ());
    MOCK_CONST_METHOD0(isReadyImpl, bool ());
    MOCK_METHOD1(initializeImpl, bool (bool force));
    MOCK_METHOD1(finalizeImpl,void (bool finalizeSubStateMachines));
    MOCK_METHOD0(subStateMachineCompleted, void ());
    MOCK_METHOD0(subStateMachineCompletedImpl, void ());

    MOCK_METHOD1_T(enterRegionImpl, void (RegionContainer* context));
    MOCK_METHOD1_T(exitRegionImpl, void (RegionContainer* context));
    MOCK_METHOD0(startingRegionThread, void ());
    MOCK_METHOD0(endingRegionThread, void ());

    virtual ~TestRegionMock()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Destructor called ..."
            );
    }

    void doStateChange(Context* context, StateBaseClass* newState)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Changing to state = " << newState << " ..."
            );
        SttclRegionBaseClass::changeState(context,newState);
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

    TestRegionMock
        ( const std::string& id = "<anonymous>"
        , sttcl::TimeDuration<> doActionFrequency = sttcl::TimeDuration<>(0,0,0,10)
        , bool loggingEnabled = false
        )
    : SttclTestMockBaseClass(id,loggingEnabled)
    , SttclRegionBaseClass(regionContainer,doActionFrequency)
    , directTransitState_(0)
    , finalizeOnNextDirectTransit_(false)
    , initialState_(0)
    {
        ON_CALL(*this, initializeImpl(_))
            .WillByDefault(Invoke(this, &SttclRegionMock::initializeImplCall));
        ON_CALL(*this, finalizeImpl(_))
            .WillByDefault(Invoke(this, &SttclRegionMock::finalizeImplCall));
        ON_CALL(*this, subStateMachineCompleted())
            .WillByDefault(Invoke(this, &SttclRegionMock::subStateMachineCompletedCall));
        ON_CALL(*this, subStateMachineCompletedImpl())
            .WillByDefault(Invoke(this, &SttclRegionMock::subStateMachineCompletedImplCall0));
        ON_CALL(*this, getInitialStateImpl())
            .WillByDefault(Invoke((const SttclRegionMock*)this, &SttclRegionMock::getInitialStateImplCall));
        ON_CALL(*this, isReadyImpl())
            .WillByDefault(Invoke((const SttclRegionMock*)this, &SttclRegionMock::isReadyImplCall));

        ON_CALL(*this, enterRegionImpl(_))
            .WillByDefault(Invoke(this, &SttclRegionMock::enterRegionImplCall));
        ON_CALL(*this, exitRegionImpl(_))
            .WillByDefault(Invoke(this, &SttclRegionMock::exitRegionImplCall));
        ON_CALL(*this, startingRegionThread())
            .WillByDefault(Invoke(this, &SttclRegionMock::startingRegionThreadCall));
        ON_CALL(*this, endingRegionThread())
            .WillByDefault(Invoke(this, &SttclRegionMock::endingRegionThreadCall));
    }

    bool isReadyImplCall() const
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Calling SttclRegionBaseClass::isReadyImpl() ..."
            );
        bool result = SttclRegionBaseClass::isReadyImpl();
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "returning reult = " << result <<  ") ..."
            );
        return result;
    }

    bool initializeImplCall(bool force)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Calling SttclRegionBaseClass::initializeImpl( force = " << force << ") ..."
            );
        bool result = SttclRegionBaseClass::initializeImpl(force);
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "returning reult = " << result <<  ") ..."
            );
        return result;
    }

    void finalizeImplCall(bool finalizeSubStateMachines)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Calling SttclRegionBaseClass::finalizeImpl( finalizeSubStateMachines = " << finalizeSubStateMachines << ") ..."
            );
        SttclRegionBaseClass::finalizeImpl(finalizeSubStateMachines);
    }

    void subStateMachineCompletedCall()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Calling SttclRegionBaseClass::subStateMachineCompleted() ..."
            );
        SttclRegionBaseClass::subStateMachineCompleted();
    }

    void subStateMachineCompletedImplCall0()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Calling SttclRegionBaseClass::subStateMachineCompletedImpl() ..."
            );
        SttclRegionBaseClass::subStateMachineCompletedImpl();
    }

    void subStateMachineCompletedImplCall1(typename IStateMachineHooks<ITestInnerStateInterface<NestingLevel> >::StateBaseClass* state)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Calling SttclRegionBaseClass::subStateMachineCompleted() ..."
            );
        RegionBaseClass::subStateMachineCompleted();
    }

    InnerStateClass* getInitialStateImplCall() const
    {
        sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
        return initialState_;
    }


    void enterRegionImplCall(RegionContainer* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Calling SttclRegionBaseClass::enterRegionImpl( context = " << context << ") ..."
            );
        SttclRegionBaseClass::enterRegionImpl(context);
    }

    void exitRegionImplCall(RegionContainer* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Calling SttclRegionBaseClass::exitRegionImpl( context = " << context << ") ..."
            );
        SttclRegionBaseClass::exitRegionImpl(context);
    }

    void startingRegionThreadCall()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Calling SttclRegionBaseClass::startingRegionThread() ..."
            );
        SttclRegionBaseClass::startingRegionThread();
    }

    void endingRegionThreadCall()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Calling SttclRegionBaseClass::endingRegionThread() ..."
            );
        SttclRegionBaseClass::endingRegionThread();
        doActionThreadExited_.post();
    }
};

template
    < typename RegionContainer
    , sttcl::RegionHistoryType::Values HistoryType = sttcl::RegionHistoryType::None
    >
class TestRegionNoArgsMock
: public TestRegionMock
      < TestRegionNoArgsMock<RegionContainer,HistoryType>
      , RegionContainer
      , ITestStateInterfaceNoArgs<RegionContainer>
      , ITestStateInterfaceNoArgs<TestRegionNoArgsMock<RegionContainer,HistoryType> >
      , HistoryType
      >
{
public:
    typedef TestRegionMock
            < TestRegionNoArgsMock<RegionContainer,HistoryType>
            , RegionContainer
            , ITestStateInterfaceNoArgs<RegionContainer>
            , ITestStateInterfaceNoArgs<TestRegionNoArgsMock<RegionContainer,HistoryType> >
            , HistoryType
            > MockBaseClass;
    typedef ITestStateInterfaceNoArgs<TestRegionNoArgsMock<RegionContainer,HistoryType> > InnerStateInterface;
    typedef typename MockBaseClass::InnerStateBaseClass InnerStateBaseClass;

    TestRegionNoArgsMock(const std::string& id = "<anonymous>", bool enableLogging = false)
    : MockBaseClass(id,enableLogging)
    {
        ON_CALL(*this,handleEvent1(_))
            .WillByDefault(Invoke(this, &TestRegionNoArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_))
            .WillByDefault(Invoke(this, &TestRegionNoArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_))
            .WillByDefault(Invoke(this, &TestRegionNoArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_))
            .WillByDefault(Invoke(this, &TestRegionNoArgsMock::handleEvent4Call));
    }

    virtual ~TestRegionNoArgsMock() {}

    MOCK_METHOD1_T(handleEvent1, void (RegionContainer* context));
    MOCK_METHOD1_T(handleEvent2, void (RegionContainer* context));
    MOCK_METHOD1_T(handleEvent3, void (RegionContainer* context));
    MOCK_METHOD1_T(handleEvent4, void (RegionContainer* context));

    virtual void handleEvent1Call(RegionContainer* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionNoArgsMock
            , "handleEvent1Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionNoArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent1( " <<
                  this << ") ..."
                );
            currentState->handleEvent1(this);
        }
    }

    virtual void handleEvent2Call(RegionContainer* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionNoArgsMock
            , "handleEvent2Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionNoArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent2( " <<
                  this << ") ..."
                );
            currentState->handleEvent2(this);
        }
    }

    virtual void handleEvent3Call(RegionContainer* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionNoArgsMock
            , "handleEvent3Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionNoArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent3( " <<
                  this << ") ..."
                );
            currentState->handleEvent3(this);
        }
    }

    virtual void handleEvent4Call(RegionContainer* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionNoArgsMock
            , "handleEvent4Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionNoArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent4( " <<
                  this << ") ..."
                );
            currentState->handleEvent4(this);
        }
    }

};

template
    < typename RegionContainer
    , sttcl::RegionHistoryType::Values HistoryType = sttcl::RegionHistoryType::None
    >
class TestRegionWithArgsMock
: public TestRegionMock
      < TestRegionWithArgsMock<RegionContainer,HistoryType>
      , RegionContainer
      , ITestStateInterfaceWithArgs<RegionContainer>
      , ITestStateInterfaceWithArgs<TestRegionWithArgsMock<RegionContainer,HistoryType> >
      , HistoryType
      >
{
public:
    typedef TestRegionMock
            < TestRegionWithArgsMock<RegionContainer,HistoryType>
            , RegionContainer
            , ITestStateInterfaceWithArgs<RegionContainer>
            , ITestStateInterfaceWithArgs<TestRegionWithArgsMock<RegionContainer,HistoryType> >
            , HistoryType
            > MockBaseClass;
    typedef typename MockBaseClass::InnerStateBaseClass InnerStateBaseClass;

    TestRegionWithArgsMock(const std::string& id = "<anonymous>", bool enableLogging = false)
    : MockBaseClass(id,enableLogging)
    {
        ON_CALL(*this,handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionWithArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestRegionWithArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_))
            .WillByDefault(Invoke(this, &TestRegionWithArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestRegionWithArgsMock::handleEvent4Call));
    }

    virtual ~TestRegionWithArgsMock() {}

    MOCK_METHOD3_T(handleEvent1, void (RegionContainer* context, const std::string& arg1, int arg2));
    MOCK_METHOD2_T(handleEvent2, void (RegionContainer* context, double arg1));
    MOCK_METHOD1_T(handleEvent3, void (RegionContainer* context));
    MOCK_METHOD2_T(handleEvent4, void (RegionContainer* context, int arg1));

    virtual void handleEvent1Call(RegionContainer* context, const std::string& arg1, int arg2)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionWithArgsMock
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
                ( TestRegionWithArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent1( " <<
                  this <<
                  ", arg1 = " << arg1 <<
                  ", arg2 = " << arg2 <<
                  ") ..."
                );
            currentState->handleEvent1(this,arg1,arg2);
        }
    }

    virtual void handleEvent2Call(RegionContainer* context, double arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionWithArgsMock
            , "handleEvent2Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionWithArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent2( " <<
                  this <<
                  ", arg1 = " << arg1 <<
                  ") ..."
                );
            currentState->handleEvent2(this,arg1);
        }
    }

    virtual void handleEvent3Call(RegionContainer* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionWithArgsMock
            , "handleEvent3Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionWithArgsMock
                , "Calling currentState[" << currentState << "]->handleEvent3( " <<
                  this <<
                  ") ..."
                );
            currentState->handleEvent3(this);
        }
    }

    virtual void handleEvent4Call(RegionContainer* context, int arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionWithArgsMock
            , "handleEvent4Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ") called ..."
            );
        // Propagate event to the current state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionWithArgsMock
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
