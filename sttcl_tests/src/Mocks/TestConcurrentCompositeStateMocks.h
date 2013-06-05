/*
 * TestConcurrentConcurrentCompositeStateMocks.h
 *
 *  Created on: May 22, 2013
 *      Author: user
 */

#ifndef TESTCONCURRENTCOMPOSITESTATEMOCKS_H_
#include <ConcurrentCompositeState.h>

#define TESTCONCURRENTCOMPOSITESTATEMOCKS_H_

#include <gmock/gmock.h>
#include <StateMachine.h>
#include "SttclTestLog.h"
#include "SttclTestMockBaseClass.h"
#include "IConcurrentCompositeStateClient.h"
#include "ITestStateInterfaceNoArgs.h"
#include "ITestStateInterfaceWithArgs.h"
#include "ITestInnerConcurrentStateInterfaceNoArgs.h"
#include "ITestInnerConcurrentStateInterfaceWithArgs.h"
#include "EventArgs.h"

template
    < typename ConcurrentCompositeStateImpl
    , typename StateMachineContext
    , typename OuterStateInterface
    , typename InnerStateInterface
    , typename EventArgsType
    , unsigned int NumOfRegions
    >
class TestConcurrentCompositeStateMock
: public SttclTestMockBaseClass
, public sttcl::ConcurrentCompositeState
            < ConcurrentCompositeStateImpl
            , StateMachineContext
            , InnerStateInterface
            , NumOfRegions
            , EventArgsType
            >
, public IConcurrentCompositeStateClient
            < StateMachineContext
            , sttcl::StateBase<StateMachineContext,OuterStateInterface>
            , typename sttcl::ConcurrentCompositeState
                           < ConcurrentCompositeStateImpl
                           , StateMachineContext
                           , InnerStateInterface
                           , NumOfRegions
                           , EventArgsType
                           >::RegionBaseType
            , sttcl::StateBase<ConcurrentCompositeStateImpl,InnerStateInterface>
            >
{
public:
    typedef TestConcurrentCompositeStateMock
                < ConcurrentCompositeStateImpl
                , StateMachineContext
                , OuterStateInterface
                , InnerStateInterface
                , EventArgsType
                , NumOfRegions
                > SelfClassType;
    typedef sttcl::ConcurrentCompositeState
                < ConcurrentCompositeStateImpl
                , StateMachineContext
                , InnerStateInterface
                , NumOfRegions
                , EventArgsType
                > SttclConcurrentCompositeStateBaseClass;
    typedef typename SttclConcurrentCompositeStateBaseClass::RegionBaseType RegionBaseType;
    typedef SttclConcurrentCompositeStateBaseClass SttclCompsiteStateMachineBaseClass;
    typedef sttcl::StateBase<StateMachineContext,OuterStateInterface> StateBaseClass;
    //typedef SttclConcurrentCompositeStateBaseClass StateBaseType;
    typedef sttcl::StateBase<ConcurrentCompositeStateImpl,InnerStateInterface> InnerStateBaseClass;
    typedef StateMachineContext Context;
//    typedef RegionBaseType RegionBaseClass;

    MOCK_METHOD1_T(entryImpl, void (StateMachineContext* context));
    MOCK_METHOD1_T(exitImpl, void (StateMachineContext* context));
    MOCK_METHOD1_T(startDoImpl, void (StateMachineContext* context));
    MOCK_METHOD1_T(endDoImpl, void (StateMachineContext* context));
    MOCK_METHOD1_T(joinDoActionImpl, void (StateMachineContext* context));
    MOCK_METHOD1_T(finalizeSubStateMachinesImpl, void (bool recursive));
    MOCK_METHOD1_T(initSubStateMachinesImpl, void (bool recursive));
    MOCK_METHOD3_T(checkDirectTransitionImpl, bool (StateMachineContext* context, bool& finalize, StateBaseClass*& nextState));

    MOCK_CONST_METHOD0(isReadyImpl, bool ());
    MOCK_METHOD1_T(initializeImpl, bool (bool force));
    MOCK_METHOD1_T(finalizeImpl, void (bool finalizeSubStateMachines));
    MOCK_METHOD1_T(regionCompletedImpl, void (RegionBaseType* state));

    virtual ~TestConcurrentCompositeStateMock()
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "Destructor called ..."
            );
    }

    void clearRegions()
    {
        for(unsigned int i = 0; i < NumOfRegions; ++i)
        {
            regions_[i] = NULL;
        }
    }

    void setRegion(unsigned int index, RegionBaseType* region)
    {
        assert(index < NumOfRegions);
        assert(region);
        regions_[index] = region;
    }

    void doStateChange(StateMachineContext* context, StateBaseClass* newState)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "Changing to state = " << newState << " ..."
            );
        SttclConcurrentCompositeStateBaseClass::changeState(context,newState);
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
    typename SttclConcurrentCompositeStateBaseClass::RegionsArray regions_;

    TestConcurrentCompositeStateMock
     ( StateMachineContext* context, const std::string& id = "<anonymous>", bool loggingEnabled = false)
    : SttclTestMockBaseClass(id,loggingEnabled)
    , SttclConcurrentCompositeStateBaseClass(context,regions_)
    , directTransitState_(0)
    , finalizeOnNextDirectTransit_(false)
    {
        ON_CALL(*this, entryImpl(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::entryImplCall));
        ON_CALL(*this, exitImpl(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::exitImplCall));
        ON_CALL(*this, startDoImpl(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::startDoImplCall));
        ON_CALL(*this, endDoImpl(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::endDoImplCall));
        ON_CALL(*this, joinDoActionImpl(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::joinDoActionImplCall));
        ON_CALL(*this, finalizeSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::finalizeSubStateMachinesImplCall));
        ON_CALL(*this, initSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::initSubStateMachinesImplCall));
        ON_CALL(*this, checkDirectTransitionImpl(_,_,_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::checkDirectTransitionImplCall));

        ON_CALL(*this, initializeImpl(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::initializeImplCall));
        ON_CALL(*this, finalizeImpl(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::finalizeImplCall));
        ON_CALL(*this, regionCompletedImpl(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateMock::regionCompletedImplCall));

        clearRegions();
    }

    void entryImplCall(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "calling SttclConcurrentCompositeStateBaseClass::entryImpl( context = " << context <<  ") ..."
            );
        SttclConcurrentCompositeStateBaseClass::entryImpl(context);
    }

    void exitImplCall(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "calling SttclConcurrentCompositeStateBaseClass::exitImpl( context = " << context <<  ") ..."
            );
        SttclConcurrentCompositeStateBaseClass::exitImpl(context);
    }

    void startDoImplCall(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "calling SttclConcurrentCompositeStateBaseClass::startDoImpl( context = " << context <<  ") ..."
            );
        SttclConcurrentCompositeStateBaseClass::startDoImpl(context);
    }

    void endDoImplCall(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "calling SttclConcurrentCompositeStateBaseClass::endDoImpl( context = " << context <<  ") ..."
            );
        SttclConcurrentCompositeStateBaseClass::endDoImpl(context);
    }

    void joinDoActionImplCall(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "calling SttclConcurrentCompositeStateBaseClass::joinDoActionImpl( context = " << context <<  ") ..."
            );
        SttclConcurrentCompositeStateBaseClass::joinDoActionImpl(context);
    }

    void finalizeSubStateMachinesImplCall(bool recursive)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "calling SttclConcurrentCompositeStateBaseClass::finalizeSubStateMachinesImpl( recursive = " << recursive <<  ") ..."
            );
        SttclConcurrentCompositeStateBaseClass::finalizeSubStateMachinesImpl(recursive);
    }

    void initSubStateMachinesImplCall(bool recursive)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "calling SttclConcurrentCompositeStateBaseClass::initSubStateMachinesImpl( recursive = " << recursive <<  ") ..."
            );
        SttclConcurrentCompositeStateBaseClass::initSubStateMachinesImpl(recursive);
    }

    bool checkDirectTransitionImplCall(StateMachineContext* context, bool& finalize, StateBaseClass*& nextState)
    {
        bool result = false;
        if(finalizeOnNextDirectTransit_)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestConcurrentCompositeStateMock
                , "finalizing on direct transition ..."
                );
            finalize = true;
            result = true;
        }
        else if(directTransitState_)
        {
            STTCL_MOCK_LOGDEBUG
                ( TestConcurrentCompositeStateMock
                , "returning configured directTransitState_ = " << directTransitState_ <<  " ..."
                );
            nextState = directTransitState_;
            result = true;
        }
        else
        {
            STTCL_MOCK_LOGDEBUG
                ( TestConcurrentCompositeStateMock
                , "calling SttclConcurrentCompositeStateBaseClass::checkDirectTransitionImpl( context = " << context <<  ") ..."
                );
            result = SttclConcurrentCompositeStateBaseClass::checkDirectTransitionImpl(context,finalize,nextState);
            STTCL_MOCK_LOGDEBUG
                ( TestConcurrentCompositeStateMock
                , "returning result = " << result <<  ", finalize = " << finalize << ", nextState = " << nextState << " ..."
                );
        }
        return result;
    }

    bool initializeImplCall(bool force)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "calling SttclConcurrentCompositeStateBaseClass::initializeImpl( force = " << force <<  ") ..."
            );
        bool result = SttclConcurrentCompositeStateBaseClass::initializeImpl(force);
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "returning initializeImpl() result = " << result << " ..."
            );
        return result;
    }

    void finalizeImplCall(bool finalizeSubStateMachines)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "calling SttclCompsiteStateMachineBaseClass::finalizeImpl( finalizeSubStateMachines = " << finalizeSubStateMachines <<  ") ..."
            );
        SttclCompsiteStateMachineBaseClass::finalizeImpl(finalizeSubStateMachines);
    }

    void regionCompletedImplCall(RegionBaseType* region)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateMock
            , "calling SttclCompsiteStateMachineBaseClass::regionCompletedImpl( region = " << region << ") ..."
            );
        SttclCompsiteStateMachineBaseClass::regionCompletedImpl(region);
    }

};

template
    < typename StateMachineContext
    , unsigned int NumOfRegions = 10
    >
class TestConcurrentCompositeStateNoArgsMock
: public TestConcurrentCompositeStateMock
      < TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions>
      , StateMachineContext
      , ITestStateInterfaceNoArgs<StateMachineContext>
      , ITestInnerConcurrentStateInterfaceNoArgs<TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions> >
      , void
      , NumOfRegions
      >
{
public:
    typedef TestConcurrentCompositeStateMock
                < TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions>
                , StateMachineContext
                , ITestStateInterfaceNoArgs<StateMachineContext>
                , ITestInnerConcurrentStateInterfaceNoArgs<TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions> >
                , void
                , NumOfRegions
                > MockBaseClass;
    typedef ITestInnerConcurrentStateInterfaceNoArgs<TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions> > InnerStateInterface;
    typedef typename MockBaseClass::InnerStateBaseClass InnerStateBaseClass;

    TestConcurrentCompositeStateNoArgsMock(StateMachineContext* context, const std::string& id = "<anonymous>", bool enableLogging = false)
    : MockBaseClass(context,id,enableLogging)
    {
        ON_CALL(*this,handleEvent1(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateNoArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateNoArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateNoArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateNoArgsMock::handleEvent4Call));
    }

    virtual ~TestConcurrentCompositeStateNoArgsMock() {}

    MOCK_METHOD1_T(handleEvent1, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent2, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent3, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent4, void (StateMachineContext* context));

    virtual void handleEvent1Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateNoArgsMock
            , "handleEvent1Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the contained regions
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateNoArgsMock
            , "Calling MockBaseClass::broadcastEvent( " <<
              " context = " << context <<
              ", handler = " << (&ITestInnerConcurrentStateInterfaceNoArgs<TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions> >::handleEvent1) <<
              ") ..."
            );
        MockBaseClass::broadcastEvent(context,&ITestInnerConcurrentStateInterfaceNoArgs<TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions> >::handleEvent1);
    }

    virtual void handleEvent2Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateNoArgsMock
            , "handleEvent2Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the contained regions
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateNoArgsMock
            , "Calling MockBaseClass::broadcastEvent( " <<
              " context = " << context <<
              ", handler = " << (&ITestInnerConcurrentStateInterfaceNoArgs<TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions> >::handleEvent2) <<
              ") ..."
            );
        MockBaseClass::broadcastEvent(context,&ITestInnerConcurrentStateInterfaceNoArgs<TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions> >::handleEvent2);
    }

    virtual void handleEvent3Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateNoArgsMock
            , "handleEvent3Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the contained regions
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateNoArgsMock
            , "Calling MockBaseClass::broadcastEvent( " <<
              " context = " << context <<
              ", handler = " << (&ITestInnerConcurrentStateInterfaceNoArgs<TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions> >::handleEvent3) <<
              ") ..."
            );
        MockBaseClass::broadcastEvent(context,&ITestInnerConcurrentStateInterfaceNoArgs<TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions> >::handleEvent3);
    }

    virtual void handleEvent4Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateNoArgsMock
            , "handleEvent4Call( context = " << context <<  ") called ..."
            );
        // Propagate event to the contained regions
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateNoArgsMock
            , "Calling MockBaseClass::broadcastEvent( " <<
              " context = " << context <<
              ", handler = " << (&ITestInnerConcurrentStateInterfaceNoArgs<TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions> >::handleEvent4) <<
              ") ..."
            );
        MockBaseClass::broadcastEvent(context,&ITestInnerConcurrentStateInterfaceNoArgs<TestConcurrentCompositeStateNoArgsMock<StateMachineContext,NumOfRegions> >::handleEvent4);
    }

};

template
    < typename StateMachineContext
    , typename EventArgsType = EventArgs
    , unsigned int NumOfRegions = 10
    >
class TestConcurrentCompositeStateWithArgsMock
: public TestConcurrentCompositeStateMock
      < TestConcurrentCompositeStateWithArgsMock<StateMachineContext, EventArgsType, NumOfRegions>
      , StateMachineContext
      , ITestStateInterfaceWithArgs<StateMachineContext>
      , ITestInnerConcurrentStateInterfaceWithArgs<TestConcurrentCompositeStateWithArgsMock<StateMachineContext, EventArgsType, NumOfRegions> >
      , EventArgsType
      , NumOfRegions
      >
{
public:
    typedef TestConcurrentCompositeStateMock
            < TestConcurrentCompositeStateWithArgsMock<StateMachineContext, EventArgsType, NumOfRegions>
            , StateMachineContext
            , ITestStateInterfaceWithArgs<StateMachineContext>
            , ITestInnerConcurrentStateInterfaceWithArgs<TestConcurrentCompositeStateWithArgsMock<StateMachineContext, EventArgsType, NumOfRegions> >
            , EventArgsType
            , NumOfRegions
            > MockBaseClass;
    typedef ITestInnerConcurrentStateInterfaceWithArgs<TestConcurrentCompositeStateWithArgsMock<StateMachineContext, EventArgsType, NumOfRegions> > InnerStateInterface;
    typedef typename MockBaseClass::InnerStateBaseClass InnerStateBaseClass;

    TestConcurrentCompositeStateWithArgsMock(StateMachineContext* context, const std::string& id = "<anonymous>", bool enableLogging = false)
    : MockBaseClass(context,id,enableLogging)
    {
        ON_CALL(*this,handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateWithArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateWithArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateWithArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestConcurrentCompositeStateWithArgsMock::handleEvent4Call));
    }

    virtual ~TestConcurrentCompositeStateWithArgsMock() {}

    MOCK_METHOD3_T(handleEvent1, void (StateMachineContext* context, const std::string& arg1, int arg2));
    MOCK_METHOD2_T(handleEvent2, void (StateMachineContext* context, double arg1));
    MOCK_METHOD1_T(handleEvent3, void (StateMachineContext* context));
    MOCK_METHOD2_T(handleEvent4, void (StateMachineContext* context, int arg1));

    virtual void handleEvent1Call(StateMachineContext* context , const std::string& arg1, int arg2)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateWithArgsMock
            , "handleEvent1Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ", arg2 = " << arg2 <<
              ") called ..."
            );
        // Propagate event to the contained regions
        EventArgsPtr eventArgs(new Event1Args(arg1,arg2));
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateWithArgsMock
            , "Calling MockBaseClass::broadcastEvent( " <<
              " context = " << context <<
              ", handler = " << &InnerStateInterface::handleEvent1 <<
              ", eventArgs = " << eventArgs.get() <<
              ") ..."
            );
        MockBaseClass::broadcastEvent(context,&InnerStateInterface::handleEvent1,eventArgs);
    }

    virtual void handleEvent2Call(StateMachineContext* context, double arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateWithArgsMock
            , "handleEvent2Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ") called ..."
            );
        // Propagate event to the contained regions
        EventArgsPtr eventArgs(new Event2Args(arg1));
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateWithArgsMock
            , "Calling MockBaseClass::broadcastEvent( " <<
              " context = " << context <<
              ", handler = " << &InnerStateInterface::handleEvent2 <<
              ", eventArgs = " << eventArgs.get() <<
              ") ..."
            );
        MockBaseClass::broadcastEvent(context,&InnerStateInterface::handleEvent2,eventArgs);
    }

    virtual void handleEvent3Call(StateMachineContext* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateWithArgsMock
            , "handleEvent3Call( context = " << context <<
              ") called ..."
            );
        // Propagate event to the contained regions
        EventArgsPtr eventArgs(new Event3Args());
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateWithArgsMock
            , "Calling MockBaseClass::broadcastEvent( " <<
              " context = " << context <<
              ", handler = " << &InnerStateInterface::handleEvent3 <<
              ", eventArgs = " << eventArgs.get() <<
              ") ..."
            );
        MockBaseClass::broadcastEvent(context,&InnerStateInterface::handleEvent3,eventArgs);
    }

    virtual void handleEvent4Call(StateMachineContext* context, int arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateWithArgsMock
            , "handleEvent4Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ") called ..."
            );
        // Propagate event to the contained regions
        EventArgsPtr eventArgs(new Event4Args(arg1));
        STTCL_MOCK_LOGDEBUG
            ( TestConcurrentCompositeStateWithArgsMock
            , "Calling MockBaseClass::broadcastEvent( " <<
              " context = " << context <<
              ", handler = " << &InnerStateInterface::handleEvent4 <<
              ", eventArgs = " << eventArgs.get() <<
              ") ..."
            );
        MockBaseClass::broadcastEvent(context,&InnerStateInterface::handleEvent4,eventArgs);
    }

};
#endif /* TESTCONCURRENTCOMPOSITESTATEMOCKS_H_ */
