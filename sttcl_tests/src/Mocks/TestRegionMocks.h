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
    , typename InnerStateInterface
    , typename EventArgsType
    , sttcl::CompositeStateHistoryType::Values HistoryType
    >
class TestRegionMock
: public SttclTestMockBaseClass
, public sttcl::Region<RegionImpl,RegionContainer,InnerStateInterface,EventArgsType,HistoryType>
, public IRegionClient
    < RegionImpl
    , RegionContainer
    , InnerStateInterface
    >
{
public:
    typedef TestRegionMock<RegionImpl,RegionContainer,InnerStateInterface,EventArgsType,HistoryType> SelfClassType;
    typedef sttcl::Region<RegionImpl,RegionContainer,InnerStateInterface,EventArgsType,HistoryType> SttclRegionBaseClass;
    typedef sttcl::StateMachine<RegionImpl,InnerStateInterface> SttclCompsiteStateMachineBaseClass;
//    typedef sttcl::StateBase<RegionContainer,OuterStateInterface> StateBaseClass;
    //typedef SttclRegionBaseClass StateBaseType;
    typedef sttcl::StateBase<RegionImpl,InnerStateInterface> InnerStateBaseClass;
    typedef RegionContainer Context;

    MOCK_CONST_METHOD0_T(getInitialStateImpl, InnerStateBaseClass* ());
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

    InnerStateBaseClass* initialState() const { return initialState_; }
    void initialState(InnerStateBaseClass* value) { initialState_ = value; }

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
    InnerStateBaseClass* initialState_;
    volatile bool doActionExited_;

    TestRegionMock
        ( RegionContainer* regionContainer
        , const std::string& id = "<anonymous>"
        , sttcl::TimeDuration<> doActionFrequency = sttcl::TimeDuration<>(0,0,0,10)
        , bool loggingEnabled = false
        )
    : SttclTestMockBaseClass(id,loggingEnabled)
    , SttclRegionBaseClass(regionContainer,doActionFrequency)
    , initialState_(0)
    , doActionExited_(false)
    {
        ON_CALL(*this, initializeImpl(_))
            .WillByDefault(Invoke(this, &TestRegionMock::initializeImplCall));
        ON_CALL(*this, finalizeImpl(_))
            .WillByDefault(Invoke(this, &TestRegionMock::finalizeImplCall));
        ON_CALL(*this, subStateMachineCompleted())
            .WillByDefault(Invoke(this, &TestRegionMock::subStateMachineCompletedCall));
        ON_CALL(*this, subStateMachineCompletedImpl())
            .WillByDefault(Invoke(this, &TestRegionMock::subStateMachineCompletedImplCall0));
        ON_CALL(*this, getInitialStateImpl())
            .WillByDefault(Invoke((const TestRegionMock*)this, &TestRegionMock::getInitialStateImplCall));
        ON_CALL(*this, isReadyImpl())
            .WillByDefault(Invoke((const TestRegionMock*)this, &TestRegionMock::isReadyImplCall));

        ON_CALL(*this, enterRegionImpl(_))
            .WillByDefault(Invoke(this, &TestRegionMock::enterRegionImplCall));
        ON_CALL(*this, exitRegionImpl(_))
            .WillByDefault(Invoke(this, &TestRegionMock::exitRegionImplCall));
        ON_CALL(*this, startingRegionThread())
            .WillByDefault(Invoke(this, &TestRegionMock::startingRegionThreadCall));
        ON_CALL(*this, endingRegionThread())
            .WillByDefault(Invoke(this, &TestRegionMock::endingRegionThreadCall));
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

    void subStateMachineCompletedImplCall1(InnerStateBaseClass* state)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Calling SttclRegionBaseClass::subStateMachineCompleted() ..."
            );
        SttclRegionBaseClass::subStateMachineCompleted();
    }

    InnerStateBaseClass* getInitialStateImplCall() const
    {
        InnerStateBaseClass* result = initialState();
        if(!result)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionMock
                , "calling SttclRegionBaseClass::getInitialStateImpl() ..."
                );
            result = SttclRegionBaseClass::getInitialStateImpl();
            STTCL_MOCK_LOGDEBUG
                ( TestRegionMock
                , "Using base class result = " << result
                );
        }
        else
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionMock
                , "Using mock initial state property: " << result
                );
        }
        return result;
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
        doActionExited_ = false;
    }

    void endingRegionThreadCall()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionMock
            , "Calling SttclRegionBaseClass::endingRegionThread() ..."
            );
        SttclRegionBaseClass::endingRegionThread();
        doActionExited_ = false;
    }
};

template
    < typename RegionContainer
    , sttcl::CompositeStateHistoryType::Values HistoryType = sttcl::CompositeStateHistoryType::None
    >
class TestRegionNoArgsMock
: public TestRegionMock
      < TestRegionNoArgsMock<RegionContainer,HistoryType>
      , RegionContainer
      , ITestInnerConcurrentStateInterfaceNoArgs<RegionContainer>
      , void
      , HistoryType
      >
{
public:
    typedef TestRegionMock
            < TestRegionNoArgsMock<RegionContainer,HistoryType>
            , RegionContainer
            , ITestInnerConcurrentStateInterfaceNoArgs<RegionContainer>
            , void
            , HistoryType
            > MockBaseClass;
    typedef ITestInnerConcurrentStateInterfaceNoArgs<RegionContainer> InnerStateInterface;
    typedef typename MockBaseClass::InnerStateBaseClass InnerStateBaseClass;
    typedef typename InnerStateInterface::RegionContextType RegionContextType;

    TestRegionNoArgsMock(RegionContainer* regionContainer, const std::string& id = "<anonymous>", bool enableLogging = false)
    : MockBaseClass(regionContainer,id,enableLogging)
    {
        ON_CALL(*this,handleEvent1(_,_))
            .WillByDefault(Invoke(this, &TestRegionNoArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestRegionNoArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_,_))
            .WillByDefault(Invoke(this, &TestRegionNoArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestRegionNoArgsMock::handleEvent4Call));
    }

    virtual ~TestRegionNoArgsMock() {}

    MOCK_METHOD2_T(handleEvent1, void (RegionContainer* context, RegionContextType* regionContext));
    MOCK_METHOD2_T(handleEvent2, void (RegionContainer* context, RegionContextType* regionContext));
    MOCK_METHOD2_T(handleEvent3, void (RegionContainer* context, RegionContextType* regionContext));
    MOCK_METHOD2_T(handleEvent4, void (RegionContainer* context, RegionContextType* regionContext));

    virtual void handleEvent1Call(RegionContainer* context, RegionContextType* regionContext)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionNoArgsMock
            , "handleEvent1Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current inner state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionNoArgsMock
                , "MockBaseClass::dispatchEvent( context = " << context <<
                  ", currentState = " << currentState <<
                  ", eventHandler = " << &InnerStateInterface::handleEvent1 << ") ..."
                );
            MockBaseClass::dispatchEvent(context,currentState,&InnerStateInterface::handleEvent1);
        }
    }

    virtual void handleEvent2Call(RegionContainer* context, RegionContextType* regionContext)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionNoArgsMock
            , "handleEvent2Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current inner state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionNoArgsMock
                , "MockBaseClass::dispatchEvent( context = " << context <<
                  ", currentState = " << currentState <<
                  ", eventHandler = " << &InnerStateInterface::handleEvent2 << ") ..."
                );
            MockBaseClass::dispatchEvent(context,currentState,&InnerStateInterface::handleEvent2);
        }
    }

    virtual void handleEvent3Call(RegionContainer* context, RegionContextType* regionContext)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionNoArgsMock
            , "handleEvent3Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current inner state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionNoArgsMock
                , "MockBaseClass::dispatchEvent( context = " << context <<
                  ", currentState = " << currentState <<
                  ", eventHandler = " << &InnerStateInterface::handleEvent3 << ") ..."
                );
            MockBaseClass::dispatchEvent(context,currentState,&InnerStateInterface::handleEvent3);
        }
    }

    virtual void handleEvent4Call(RegionContainer* context, RegionContextType* regionContext)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionNoArgsMock
            , "handleEvent4Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the current inner state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionNoArgsMock
                , "MockBaseClass::dispatchEvent( context = " << context <<
                  ", currentState = " << currentState <<
                  ", eventHandler = " << &InnerStateInterface::handleEvent3 << ") ..."
                );
            MockBaseClass::dispatchEvent(context,currentState,&InnerStateInterface::handleEvent4);
        }
    }

};

template
    < typename RegionContainer
    , sttcl::CompositeStateHistoryType::Values HistoryType = sttcl::CompositeStateHistoryType::None
    >
class TestRegionWithArgsMock
: public TestRegionMock
      < TestRegionNoArgsMock<RegionContainer,HistoryType>
      , RegionContainer
      , ITestInnerConcurrentStateInterfaceNoArgs<RegionContainer>
      , EventArgs
      , HistoryType
      >
{
public:
    typedef TestRegionMock
            < TestRegionNoArgsMock<RegionContainer,HistoryType>
            , RegionContainer
            , ITestInnerConcurrentStateInterfaceWithArgs<RegionContainer>
            , EventArgs
            , HistoryType
            > MockBaseClass;
    typedef ITestInnerConcurrentStateInterfaceWithArgs<RegionContainer> InnerStateInterface;
    typedef typename MockBaseClass::InnerStateBaseClass InnerStateBaseClass;
    typedef typename InnerStateInterface::RegionContextType RegionContextType;

    TestRegionWithArgsMock(RegionContainer* regionContainer, const std::string& id = "<anonymous>", bool enableLogging = false)
    : MockBaseClass(regionContainer,id,enableLogging)
    {
        ON_CALL(*this,handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionWithArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionWithArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionWithArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionWithArgsMock::handleEvent4Call));
    }

    virtual ~TestRegionWithArgsMock() {}

    MOCK_METHOD3_T(handleEvent1, void (RegionContainer* context, RegionContextType* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3_T(handleEvent2, void (RegionContainer* context, RegionContextType* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3_T(handleEvent3, void (RegionContainer* context, RegionContextType* regionContext, EventArgsPtr eventArgs));
    MOCK_METHOD3_T(handleEvent4, void (RegionContainer* context, RegionContextType* regionContext, EventArgsPtr eventArgs));

    void handleEvent1Call(RegionContainer* context, RegionContextType* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionWithArgsMock
            , "handleEvent1Call( context = " << context <<
              ", regionContext = " << regionContext <<
              ", eventArgs = " << eventArgs.get() <<
              ") called ..."
            );
        // Propagate event to the current inner state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionWithArgsMock
                , "MockBaseClass::dispatchEvent( context = " << context <<
                  ", currentState = " << currentState <<
                  ", eventHandler = " << &InnerStateInterface::handleEvent1 <<
                  ", eventArgs = " << eventArgs.get() <<
                  ") ..."
                );
            MockBaseClass::dispatchEvent(context,currentState,&InnerStateInterface::handleEvent1,eventArgs);
        }
    }

    void handleEvent2Call(RegionContainer* context, RegionContextType* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionWithArgsMock
            , "handleEvent2Call( context = " << context <<
              ", regionContext = " << regionContext <<
              ", eventArgs = " << eventArgs.get() <<
              ") called ..."
            );
        // Propagate event to the current inner state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionWithArgsMock
                , "MockBaseClass::dispatchEvent( context = " << context <<
                  ", currentState = " << currentState <<
                  ", eventHandler = " << &InnerStateInterface::handleEvent2 <<
                  ", eventArgs = " << eventArgs.get() <<
                  ") ..."
                );
            MockBaseClass::dispatchEvent(context,currentState,&InnerStateInterface::handleEvent2,eventArgs);
        }
    }

    void handleEvent3Call(RegionContainer* context, RegionContextType* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionWithArgsMock
            , "handleEvent3Call( context = " << context <<
              ", regionContext = " << regionContext <<
              ", eventArgs = " << eventArgs.get() <<
              ") called ..."
            );
        // Propagate event to the current inner state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionWithArgsMock
                , "MockBaseClass::dispatchEvent( context = " << context <<
                  ", currentState = " << currentState <<
                  ", eventHandler = " << &InnerStateInterface::handleEvent3 <<
                  ", eventArgs = " << eventArgs.get() <<
                  ") ..."
                );
            MockBaseClass::dispatchEvent(context,currentState,&InnerStateInterface::handleEvent3,eventArgs);
        }
    }

    void handleEvent4Call(RegionContainer* context, RegionContextType* regionContext, EventArgsPtr eventArgs)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionWithArgsMock
            , "handleEvent4Call( context = " << context <<
              ", regionContext = " << regionContext <<
              ", eventArgs = " << eventArgs.get() <<
              ") called ..."
            );
        // Propagate event to the current inner state
        InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestRegionWithArgsMock
                , "MockBaseClass::dispatchEvent( context = " << context <<
                  ", currentState = " << currentState <<
                  ", eventHandler = " << &InnerStateInterface::handleEvent4 <<
                  ", eventArgs = " << eventArgs.get() <<
                  ") ..."
                );
            MockBaseClass::dispatchEvent(context,currentState,&InnerStateInterface::handleEvent4,eventArgs);
        }
    }

};
#endif /* TESTCOMPOSITESTATEMOCKS_H_ */
