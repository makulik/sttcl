/*
 * SttclConcurrentCompositeStateWithArgsMock.h
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
#include "ITestStateInterfaceWithArgs.h"
#include "ITestConcurrentStateMachineWithArgs.h"
#include "IConcurrentCompositeStateWithArgsHooks.h"
#include "SttclTestLog.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template
    < class CompositeStateImpl
    , class StateMachineContext
    , class InnerStateInterface
    >
class SttclConcurrentCompositeStateWithArgsMock
: public sttcl::ConcurrentCompositeState<CompositeStateImpl,StateMachineContext,InnerStateInterface,255,EventArgs>
, public IConcurrentCompositeStateWithArgsHooks<CompositeStateImpl,StateMachineContext,InnerStateInterface>
{
public:

	typedef sttcl::ConcurrentCompositeState<CompositeStateImpl,StateMachineContext,InnerStateInterface,255,EventArgs> StateMachineBaseClass;
    typedef typename StateMachineBaseClass::StateImplementationBase StateBaseClass;
    //typedef typename StateMachineBaseClass::RegionsArray RegionsArrayType;
    typedef typename IConcurrentCompositeStateWithArgsHooks<CompositeStateImpl,StateMachineContext,InnerStateInterface>::RegionBaseClass RegionBaseClass;
    // typedef typename StateMachineBaseClass::MutexT

	SttclConcurrentCompositeStateWithArgsMock(StateMachineContext* context, const std::string& stateMachineId = "<anonymous>")
	: StateMachineBaseClass(context,regions)
	, enableLogs_(false)
	, stateMachineId_(stateMachineId)
    , directTransitState_(NULL)
    , finalizeOnNextDirectTransitCheck_(false)
	{
		ON_CALL(*this, initializeImpl(_))
			.WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::initializeImplCall));
		ON_CALL(*this, finalizeImpl(_))
			.WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::finalizeImplCall));
//		ON_CALL(*this, subStateMachineCompleted())
//			.WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::subStateMachineCompletedCall));
//        ON_CALL(*this, subStateMachineCompletedImpl())
//            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::subStateMachineCompletedImplCall0));

        ON_CALL(*this, entryImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::entryImplCall));
        ON_CALL(*this, exitImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::exitImplCall));
        ON_CALL(*this, startDoImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::startDoImplCall));
        ON_CALL(*this, endDoImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::endDoImplCall));
        ON_CALL(*this, finalizeSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::finalizeSubStateMachinesImplCall));
        ON_CALL(*this, initSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::initSubStateMachinesImplCall));
        ON_CALL(*this, checkDirectTransitionImpl(_,_,_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::checkDirectTransitionImplCall));
        ON_CALL(*this, doActionImpl(_,_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::doActionImplCall));
        ON_CALL(*this, joinDoActionImpl(_))
            .WillByDefault(Invoke(this, &SttclConcurrentCompositeStateWithArgsMock::joinDoActionImplCall));

        clearRegions();
    }

	virtual ~SttclConcurrentCompositeStateWithArgsMock()
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

	// IStateMachineWithArgsHooks
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
    MOCK_METHOD3_T(checkDirectTransitionImpl, bool (StateMachineContext* context, bool& finalize, sttcl::StateBase<StateMachineContext,ITestStateInterfaceWithArgs>*& nextState));
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
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateMachineBaseClass::isReadyImpl() ...");
    	return SttclConcurrentCompositeStateWithArgsMock::StateMachineBaseClass::isReadyImpl();
    }

    bool initializeImplCall(bool force)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateMachineBaseClass::initializeImpl(" << force << ") ...");
    	return StateMachineBaseClass::initializeImpl(force);
    }

    void finalizeImplCall(bool finalizeSubStateMachines)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateMachineBaseClass::finalizeImpl(" << finalizeSubStateMachines << ") ...");
		StateMachineBaseClass::finalizeImpl(finalizeSubStateMachines);
    }

    void regionCompletedCall(RegionBaseClass* region)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateMachineBaseClass::regionCompletedCall(" << region << ") ...");
        StateMachineBaseClass::regionCompletedCall(region);
    }

//    void subStateMachineCompletedCall()
//    {
//        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateMachineBaseClass::subStateMachineCompleted() ...");
//        StateMachineBaseClass::subStateMachineCompleted();
//    }
//
//    void subStateMachineCompletedImplCall0()
//    {
//        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateMachineBaseClass::subStateMachineCompletedImpl() ...");
//        StateMachineBaseClass::subStateMachineCompletedImpl();
//    }

    void subStateMachineCompletedImplCall1(IStateMachineWithArgsHooks<ITestConcurrentStateMachineWithArgs>::StateBaseClass* state)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateMachineBaseClass::subStateMachineCompletedImpl() ...");
        StateMachineBaseClass::subStateMachineCompleted();
    }

    void entryImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateBaseClass::entryImpl( context = " << context << ") ...");
        StateMachineBaseClass::entryImpl(context);
    }

    void exitImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateBaseClass::exitImpl( context = " << context << ") ...");
        StateMachineBaseClass::exitImpl(context);
    }

    void startDoImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " startDoImplCall( context = " << context << ") ...");
    }

    void endDoImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateBaseClass::endDoImpl( context = " << context << ") ...");
        StateMachineBaseClass::endDoImpl(context);
    }

    void finalizeSubStateMachinesImplCall(bool recursive)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateBaseClass::finalizeSubStateMachinesImpl(" << recursive << ") ...");
        StateMachineBaseClass::finalizeSubStateMachinesImpl(recursive);
    }

    void initSubStateMachinesImplCall(bool recursive)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateBaseClass::initSubStateMachinesImpl(" << recursive << ") ...");
        StateMachineBaseClass::initSubStateMachinesImpl(recursive);
    }

    bool checkDirectTransitionImplCall(StateMachineContext* context, bool& finalize, sttcl::StateBase<StateMachineContext,ITestStateInterfaceWithArgs>*& nextState)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateBaseClass::checkDirectTransitionImpl( context = " << context << ", finalize = " << finalize << ", nextState = " << nextState << ") ...");
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
        STTCL_TEST_LOG(logsEnabled(), id() << " SttclConcurrentCompositeStateWithArgsMock::doActionImplCall( context = " << context << ", firstCall = " << firstCall);
    }

    void joinDoActionImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclConcurrentCompositeStateWithArgsMock::StateBaseClass::joinDoActionImpl(" << context << ") ...");
        StateMachineBaseClass::joinDoActionImpl(context);
    }

};
#endif /* STTCLCONCURRENTCOMPOSITESTATEMOCK_H_ */
