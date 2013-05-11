/*
 * SttclCompositeStateWithArgsMock.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef STTCLCOMPOSITESTATEWITHARGSMOCK_H_
#define STTCLCOMPOSITESTATEWITHARGSMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <CompositeState.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestStateInterfaceWithArgs.h"
#include "ITestInnerStateInterfaceWithArgs.h"
#include "ICompositeStateWithArgsHooks.h"
#include "SttclTestLog.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template
    < class CompositeStateImpl
    , class StateMachineContext
    , class InnerStateInterface
    >
class SttclCompositeStateWithArgsMock
: public sttcl::CompositeState<CompositeStateImpl,StateMachineContext,InnerStateInterface>
, public ICompositeStateWithArgsHooks<CompositeStateImpl,StateMachineContext,InnerStateInterface>
{
public:

	typedef sttcl::CompositeState<CompositeStateImpl,StateMachineContext,InnerStateInterface> StateMachineBaseClass;
    typedef typename StateMachineBaseClass::StateImplementationBase StateBaseClass;
    typedef typename StateMachineBaseClass::InnerStateClass InnerStateClass;

	SttclCompositeStateWithArgsMock(const std::string& stateMachineId = "<anonymous>", InnerStateClass* initialState = NULL)
	: initialState_(initialState)
	, enableLogs_(false)
	, stateMachineId_(stateMachineId)
    , directTransitState_(NULL)
    , finalizeOnNextDirectTransitCheck_(false)
	{
		ON_CALL(*this, initializeImpl(_))
			.WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::initializeImplCall));
		ON_CALL(*this, finalizeImpl(_))
			.WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::finalizeImplCall));
		ON_CALL(*this, subStateMachineCompleted())
			.WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::subStateMachineCompletedCall));
        ON_CALL(*this, subStateMachineCompletedImpl())
            .WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::subStateMachineCompletedImplCall0));
		ON_CALL(*this, getInitialStateImpl())
			.WillByDefault(Invoke((const SttclCompositeStateWithArgsMock*)this, &SttclCompositeStateWithArgsMock::getInitialStateImplCall));
		ON_CALL(*this, isReadyImpl())
			.WillByDefault(Invoke((const SttclCompositeStateWithArgsMock*)this, &SttclCompositeStateWithArgsMock::isReadyImplCall));

        ON_CALL(*this, entryImpl(_))
            .WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::entryImplCall));
        ON_CALL(*this, exitImpl(_))
            .WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::exitImplCall));
        ON_CALL(*this, startDoImpl(_))
            .WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::startDoImplCall));
        ON_CALL(*this, endDoImpl(_))
            .WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::endDoImplCall));
        ON_CALL(*this, finalizeSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::finalizeSubStateMachinesImplCall));
        ON_CALL(*this, initSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::initSubStateMachinesImplCall));
        ON_CALL(*this, checkDirectTransitionImpl(_,_,_))
            .WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::checkDirectTransitionImplCall));
        ON_CALL(*this, doActionImpl(_,_))
            .WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::doActionImplCall));
        ON_CALL(*this, joinDoActionImpl(_))
            .WillByDefault(Invoke(this, &SttclCompositeStateWithArgsMock::joinDoActionImplCall));
}

	virtual ~SttclCompositeStateWithArgsMock()
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

	void setInitialState(InnerStateClass* initialState)
	{
    	sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
		initialState_ = initialState;
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

	// ITestStateInterfaceWithArgs
    MOCK_METHOD1_T(handleEvent1, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent2, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent3, void (StateMachineContext* context));
    MOCK_METHOD1_T(handleEvent4, void (StateMachineContext* context));

	// IStateMachineWithArgsHooks
	MOCK_METHOD1(initializeImpl, bool (bool force));
	MOCK_METHOD1(finalizeImpl,void (bool finalizeSubStateMachines));
    MOCK_METHOD0(subStateMachineCompleted, void ());
    MOCK_METHOD0(subStateMachineCompletedImpl, void ());
    MOCK_CONST_METHOD0_T(getInitialStateImpl, InnerStateClass* ());
    MOCK_CONST_METHOD0(isReadyImpl, bool ());

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
	InnerStateClass* initialState_;
    bool enableLogs_;
    std::string stateMachineId_;
    typename StateBaseClass::StateBaseType* directTransitState_;
    bool finalizeOnNextDirectTransitCheck_;

private:
	bool isReadyImplCall() const
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclCompositeStateWithArgsMock::StateMachineBaseClass::isReadyImpl() ...");
    	return SttclCompositeStateWithArgsMock::StateMachineBaseClass::isReadyImpl();
    }

    bool initializeImplCall(bool force)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclCompositeStateWithArgsMock::StateMachineBaseClass::initializeImpl(" << force << ") ...");
    	return StateMachineBaseClass::initializeImpl(force);
    }

    void finalizeImplCall(bool finalizeSubStateMachines)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclCompositeStateWithArgsMock::StateMachineBaseClass::finalizeImpl(" << finalizeSubStateMachines << ") ...");
		StateMachineBaseClass::finalizeImpl(finalizeSubStateMachines);
    }

    void subStateMachineCompletedCall()
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclCompositeStateWithArgsMock::StateMachineBaseClass::subStateMachineCompleted() ...");
        StateMachineBaseClass::subStateMachineCompleted();
    }

    void subStateMachineCompletedImplCall0()
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclCompositeStateWithArgsMock::StateMachineBaseClass::subStateMachineCompletedImpl() ...");
        StateMachineBaseClass::subStateMachineCompletedImpl();
    }

    void subStateMachineCompletedImplCall1(IStateMachineWithArgsHooks<ITestInnerStateInterfaceWithArgs>::StateBaseClass* state)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclCompositeStateWithArgsMock::StateMachineBaseClass::subStateMachineCompletedImpl() ...");
        StateMachineBaseClass::subStateMachineCompleted();
    }

    InnerStateClass* getInitialStateImplCall() const
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " SttclCompositeStateWithArgsMock::getInitialStateImplCall(), initialState: = " << initialState_);
    	sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
    	return initialState_;
    }


    void entryImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclCompositeStateWithArgsMock::::entryImpl( context = " << context << ") ...");
        StateMachineBaseClass::entryImpl(context);
    }

    void exitImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclCompositeStateWithArgsMock::::exitImpl( context = " << context << ") ...");
        StateMachineBaseClass::exitImpl(context);
    }

    void startDoImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling StateMachineBaseClass::startDoImpl( context = " << context << ") ...");
        StateMachineBaseClass::startDoImpl(context);
    }

    void endDoImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling StateMachineBaseClass::endDoImpl( context = " << context << ") ...");
        StateMachineBaseClass::endDoImpl(context);
    }

    void finalizeSubStateMachinesImplCall(bool recursive)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling StateMachineBaseClass::finalizeSubStateMachinesImpl(" << recursive << ") ...");
        StateMachineBaseClass::finalizeSubStateMachinesImpl(recursive);
    }

    void initSubStateMachinesImplCall(bool recursive)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling StateMachineBaseClass::initSubStateMachinesImpl(" << recursive << ") ...");
        StateMachineBaseClass::initSubStateMachinesImpl(recursive);
    }

    bool checkDirectTransitionImplCall(StateMachineContext* context, bool& finalize, sttcl::StateBase<StateMachineContext,ITestStateInterfaceWithArgs>*& nextState)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling StateMachineBaseClass::checkDirectTransitionImpl( context = " << context << ", finalize = " << finalize << ", nextState = " << nextState << ") ...");
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
        STTCL_TEST_LOG(logsEnabled(), id() << " SttclCompositeStateWithArgsMock::doActionImplCall( context = " << context << ", firstCall = " << firstCall);
    }

    void joinDoActionImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling StateMachineBaseClass::joinDoActionImpl(" << context << ") ...");
        StateMachineBaseClass::joinDoActionImpl(context);
    }

};
#endif /* STTCLCOMPOSITESTATEWITHARGSMOCK_H_ */
