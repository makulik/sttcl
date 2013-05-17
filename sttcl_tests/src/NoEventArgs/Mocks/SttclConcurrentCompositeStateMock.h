/*
 * SttclConcurrentCompositeStateMock.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef STTCLCONCURRENTCOMPOSITESTATEMOCK_H_
#define STTCLCONCURRENTCOMPOSITESTATEMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <ConcurrentCompositeState.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestStateInterface.h"
#include "ITestConcurrentStateMachine.h"
#include "IConcurrentCompositeStateHooks.h"
#include "SttclTestLog.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template
    < class CompositeStateImpl
    , class StateMachineContext
    , class InnerStateInterface
    , unsigned int NestingLevel = 0
    >
class SttclConcurrentCompositeStateMock
: public sttcl::ConcurrentCompositeState<CompositeStateImpl,StateMachineContext,InnerStateInterface,255>
, public IConcurrentCompositeStateHooks<CompositeStateImpl,StateMachineContext,InnerStateInterface>
{
public:

	typedef sttcl::ConcurrentCompositeState<CompositeStateImpl,StateMachineContext,InnerStateInterface,255> StateMachineBaseClass;
    typedef typename StateMachineBaseClass::StateImplementationBase StateBaseClass;
    //typedef typename StateMachineBaseClass::RegionsArray RegionsArrayType;
    typedef typename IConcurrentCompositeStateHooks<CompositeStateImpl,StateMachineContext,InnerStateInterface>::RegionBaseClass RegionBaseClass;
    // typedef typename StateMachineBaseClass::MutexT

	SttclConcurrentCompositeStateMock(StateMachineContext* context, const std::string& stateMachineId = "<anonymous>")
	: StateMachineBaseClass(context,regions)
	, enableLogs_(false)
	, stateMachineId_(stateMachineId)
    , directTransitState_(NULL)
    , finalizeOnNextDirectTransitCheck_(false)
	{
		ON_CALL(*this, initializeImpl(_))
			.WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::initializeImplCall));
		ON_CALL(*this, finalizeImpl(_))
			.WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::finalizeImplCall));
//		ON_CALL(*this, subStateMachineCompleted())
//			.WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::subStateMachineCompletedCall));
//        ON_CALL(*this, subStateMachineCompletedImpl())
//            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::subStateMachineCompletedImplCall0));

        ON_CALL(*this, entryImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::entryImplCall));
        ON_CALL(*this, exitImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::exitImplCall));
        ON_CALL(*this, startDoImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::startDoImplCall));
        ON_CALL(*this, endDoImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::endDoImplCall));
        ON_CALL(*this, finalizeSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::finalizeSubStateMachinesImplCall));
        ON_CALL(*this, initSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::initSubStateMachinesImplCall));
        ON_CALL(*this, checkDirectTransitionImpl(_,_,_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::checkDirectTransitionImplCall));
        ON_CALL(*this, doActionImpl(_,_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::doActionImplCall));
        ON_CALL(*this, joinDoActionImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateMock::joinDoActionImplCall));

        clearRegions();
    }

	virtual ~SttclConcurrentCompositeStateMock()
	{
	}

	const std::string& id() const { return stateMachineId_; }

    void enableLogs(bool enable)
    {
        enableLogs_ = enable;
    }

    bool logsEnabled() const
    {
        return enableLogs_;
    }

    void setDirectTransitState(typename StateBaseClass::StateBaseType* directTransitState)
    {
        sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
        directTransitState_ = directTransitState;
    }

    void doStateChange(StateMachineContext* context, typename StateBaseClass::StateBaseType* newState)
    {
        StateBaseClass::changeState(context,newState);
    }

    void finalizeOnNextDirectTransitCheck()
    {
        sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
        finalizeOnNextDirectTransitCheck_ = true;
        directTransitState_ = NULL;
    }

    void clearRegions()
    {
        for(unsigned int i = 0; i < 255; ++i)
        {
            regions[i] = NULL;
        }
    }

    void setRegion(unsigned int index, RegionBaseClass* region)
    {
        assert(index < 255);
        assert(region);
        regions[index] = region;
    }

	// ITestStateInterface
    MOCK_METHOD1_T(handleEvent1, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent2, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent3, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent4, void (StateMachineContext* context));

	// IStateMachineHooks
	MOCK_METHOD1(initializeImpl, bool (bool force));
	MOCK_METHOD1(finalizeImpl,void (bool finalizeSubStateMachines));
//    MOCK_METHOD0(subStateMachineCompleted, void ());
//    MOCK_METHOD0(subStateMachineCompletedImpl, void ());
    MOCK_METHOD1_T(regionCompletedImpl, void(RegionBaseClass* region));

    // IStateHooks
    MOCK_METHOD1_T(entryImpl, void (StateMachineContext* context));
    MOCK_METHOD1_T(exitImpl, void (StateMachineContext* context));
    MOCK_METHOD1_T(startDoImpl, void (StateMachineContext* context));
    MOCK_METHOD1_T(endDoImpl, void (StateMachineContext* context));
    MOCK_METHOD1(finalizeSubStateMachinesImpl, void (bool recursive));
    MOCK_METHOD1(initSubStateMachinesImpl, void (bool recursive));
    MOCK_METHOD3_T(checkDirectTransitionImpl, bool (StateMachineContext* context, bool& finalize, sttcl::StateBase<StateMachineContext,ITestStateInterface>*& nextState));
    MOCK_METHOD2_T(doActionImpl, void (StateMachineContext* context, bool firstCall));
    MOCK_METHOD1_T(joinDoActionImpl, void (StateMachineContext* context));


protected:

	mutable sttcl::internal::SttclMutex<> internalGuard_;
    bool enableLogs_;
    std::string stateMachineId_;
    typename StateBaseClass::StateBaseType* directTransitState_;
    bool finalizeOnNextDirectTransitCheck_;

    typename StateMachineBaseClass::RegionsArray regions;

private:
	bool isReadyImplCall() const
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateMachineBaseClass::isReadyImpl() ...");
    	return SttclConcurrentCompositeStateMock::StateMachineBaseClass::isReadyImpl();
    }

    bool initializeImplCall(bool force)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateMachineBaseClass::initializeImpl(" << force << ") ...");
    	return StateMachineBaseClass::initializeImpl(force);
    }

    void finalizeImplCall(bool finalizeSubStateMachines)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateMachineBaseClass::finalizeImpl(" << finalizeSubStateMachines << ") ...");
		StateMachineBaseClass::finalizeImpl(finalizeSubStateMachines);
    }

    void regionCompletedCall(RegionBaseClass* region)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateMachineBaseClass::regionCompletedCall(" << region << ") ...");
        StateMachineBaseClass::regionCompletedCall(region);
    }

//    void subStateMachineCompletedCall()
//    {
//        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateMachineBaseClass::subStateMachineCompleted() ...");
//        StateMachineBaseClass::subStateMachineCompleted();
//    }
//
//    void subStateMachineCompletedImplCall0()
//    {
//        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateMachineBaseClass::subStateMachineCompletedImpl() ...");
//        StateMachineBaseClass::subStateMachineCompletedImpl();
//    }
//
//    void subStateMachineCompletedImplCall1(IStateMachineHooks<typename ITestConcurrentStateMachine<NestingLevel + 1> >::StateBaseClass* state)
//    {
//        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateMachineBaseClass::subStateMachineCompletedImpl() ...");
//        StateMachineBaseClass::subStateMachineCompleted();
//    }

    void entryImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateBaseClass::entryImpl( context = " << context << ") ...");
        StateMachineBaseClass::entryImpl(context);
    }

    void exitImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateBaseClass::exitImpl( context = " << context << ") ...");
        StateMachineBaseClass::exitImpl(context);
    }

    void startDoImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " startDoImplCall( context = " << context << ") ...");
    }

    void endDoImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateBaseClass::endDoImpl( context = " << context << ") ...");
        StateMachineBaseClass::endDoImpl(context);
    }

    void finalizeSubStateMachinesImplCall(bool recursive)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateBaseClass::finalizeSubStateMachinesImpl(" << recursive << ") ...");
        StateMachineBaseClass::finalizeSubStateMachinesImpl(recursive);
    }

    void initSubStateMachinesImplCall(bool recursive)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateBaseClass::initSubStateMachinesImpl(" << recursive << ") ...");
        StateMachineBaseClass::initSubStateMachinesImpl(recursive);
    }

    bool checkDirectTransitionImplCall(StateMachineContext* context, bool& finalize, sttcl::StateBase<StateMachineContext,ITestStateInterface>*& nextState)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateBaseClass::checkDirectTransitionImpl( context = " << context << ", finalize = " << finalize << ", nextState = " << nextState << ") ...");
        sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
        if(!StateMachineBaseClass::checkDirectTransitionImpl(context,finalize,nextState))
        {
            if(directTransitState_)
            {
                nextState = directTransitState_;
                return true;
            }
            else if(finalizeOnNextDirectTransitCheck_)
            {
                finalizeOnNextDirectTransitCheck_ = false;
                nextState = NULL;
                finalize = true;
                return true;
            }

        }
        else
        {
            return true;
        }
        return false;
    }

    void doActionImplCall(StateMachineContext* context, bool firstCall)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " SttclConcurrentCompositeStateMock::doActionImplCall( context = " << context << ", firstCall = " << firstCall);
    }

    void joinDoActionImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateMock::StateBaseClass::joinDoActionImpl(" << context << ") ...");
        StateMachineBaseClass::joinDoActionImpl(context);
    }

};
#endif /* STTCLCONCURRENTCOMPOSITESTATEMOCK_H_ */
