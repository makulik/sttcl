/*
 * SttclStateWithArgsMock.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef STTCLSTATEWITHARGSMOCK_H_
#define STTCLSTATEWITHARGSMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestStateInterfaceWithArgs.h"
#include "IStateMachineWithArgsHooks.h"
#include "IStateWithArgsHooks.h"
#include "SttclTestLog.h"


using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template
    < class StateMachineContext
    , class StateInterface
    >
class SttclStateWithArgsMock
: public sttcl::State<SttclStateWithArgsMock<StateMachineContext,StateInterface>,StateMachineContext,StateInterface>
, public IStateWithArgsHooks<StateMachineContext>
{
public:
	typedef sttcl::State<SttclStateWithArgsMock<StateMachineContext,StateInterface>,StateMachineContext,StateInterface> StateBaseClass;

	virtual ~SttclStateWithArgsMock() {}

	const std::string& id() const { return stateId_; }

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

    void doStateChange(StateMachineContext* context, typename StateBaseClass::StateBaseType* newState)
    {
        StateBaseClass::changeState(context,newState);
    }

	MOCK_METHOD1_T(entryImpl, void (StateMachineContext* context));
	MOCK_METHOD1_T(exitImpl, void (StateMachineContext* context));
	MOCK_METHOD1_T(startDoImpl, void (StateMachineContext* context));
	MOCK_METHOD1_T(endDoImpl, void (StateMachineContext* context));
	MOCK_METHOD1(finalizeSubStateMachinesImpl, void (bool recursive));
	MOCK_METHOD1(initSubStateMachinesImpl, void (bool recursive));
	MOCK_METHOD3_T(checkDirectTransitionImpl, bool (StateMachineContext* context, bool& finalize, typename StateBaseClass::StateBaseType*& nextState));
    MOCK_METHOD2_T(doActionImpl, void (StateMachineContext* context, bool firstCall));
    MOCK_METHOD1_T(joinDoActionImpl, void (StateMachineContext* context));

protected:
    SttclStateWithArgsMock(const std::string& stateId = "<anonymous>")
    : StateBaseClass(&SttclStateWithArgsMock<StateMachineContext,StateInterface>::doActionImplCall)
    , stateId_(stateId)
    , directTransitState_(NULL)
    , finalizeOnNextDirectTransitCheck_(false)
    , enableLogs_(false)
    , internalGuard_()
    {
        ON_CALL(*this, entryImpl(_))
            .WillByDefault(Invoke(this, &SttclStateWithArgsMock<StateMachineContext,StateInterface>::entryImplCall));
        ON_CALL(*this, exitImpl(_))
            .WillByDefault(Invoke(this, &SttclStateWithArgsMock<StateMachineContext,StateInterface>::exitImplCall));
        ON_CALL(*this, startDoImpl(_))
            .WillByDefault(Invoke(this, &SttclStateWithArgsMock<StateMachineContext,StateInterface>::startDoImplCall));
        ON_CALL(*this, endDoImpl(_))
            .WillByDefault(Invoke(this, &SttclStateWithArgsMock<StateMachineContext,StateInterface>::endDoImplCall));
        ON_CALL(*this, finalizeSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &SttclStateWithArgsMock<StateMachineContext,StateInterface>::finalizeSubStateMachinesImplCall));
        ON_CALL(*this, initSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &SttclStateWithArgsMock<StateMachineContext,StateInterface>::initSubStateMachinesImplCall));
        ON_CALL(*this, checkDirectTransitionImpl(_,_,_))
            .WillByDefault(Invoke(this, &SttclStateWithArgsMock<StateMachineContext,StateInterface>::checkDirectTransitionImplCall));
        ON_CALL(*this, doActionImpl(_,_))
            .WillByDefault(Invoke(this, &SttclStateWithArgsMock<StateMachineContext,StateInterface>::doActionImplCall));
        ON_CALL(*this, joinDoActionImpl(_))
            .WillByDefault(Invoke(this, &SttclStateWithArgsMock<StateMachineContext,StateInterface>::joinDoActionImplCall));
    }

    void entryImplCall(StateMachineContext* context)
	{
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclStateWithArgsMock::StateBaseClass::entryImpl( context = " << context << ") ...");
		StateBaseClass::entryImpl(context);
	}

	void exitImplCall(StateMachineContext* context)
	{
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclStateWithArgsMock::StateBaseClass::exitImpl( context = " << context << ") ...");
		StateBaseClass::exitImpl(context);
	}

	void startDoImplCall(StateMachineContext* context)
	{
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclStateWithArgsMock::StateBaseClass::startDoImpl( context = " << context << ") ...");
		StateBaseClass::startDoImpl(context);
	}

	void endDoImplCall(StateMachineContext* context)
	{
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclStateWithArgsMock::StateBaseClass::endDoImpl( context = " << context << ") ...");
		StateBaseClass::endDoImpl(context);
	}

	void finalizeSubStateMachinesImplCall(bool recursive)
	{
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclStateWithArgsMock::StateBaseClass::finalizeSubStateMachinesImpl(" << recursive << ") ...");
		StateBaseClass::finalizeSubStateMachinesImpl(recursive);
	}

	void initSubStateMachinesImplCall(bool recursive)
	{
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclStateWithArgsMock::StateBaseClass::initSubStateMachinesImpl(" << recursive << ") ...");
		StateBaseClass::initSubStateMachinesImpl(recursive);
	}

	bool checkDirectTransitionImplCall(StateMachineContext* context, bool& finalize, typename StateBaseClass::StateBaseType*& nextState)
	{
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclStateWithArgsMock::StateBaseClass::checkDirectTransitionImpl( context = " << context << ", finalize = " << finalize << ", nextState = " << nextState << ") ...");
		sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
		if(!StateBaseClass::checkDirectTransitionImpl(context,finalize,nextState))
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
        STTCL_TEST_LOG(logsEnabled(), id() << " SttclStateWithArgsMock::doActionImplCall( context = " << context << ", firstCall = " << firstCall);
	}

    void joinDoActionImplCall(StateMachineContext* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclStateWithArgsMock::StateBaseClass::joinDoActionImpl(" << context << ") ...");
        StateBaseClass::joinDoActionImpl(context);
    }

    std::string stateId_;
    typename StateBaseClass::StateBaseType* directTransitState_;
	bool finalizeOnNextDirectTransitCheck_;
	bool enableLogs_;
    mutable sttcl::internal::SttclMutex<> internalGuard_;
};

#endif /* STTCLSTATEWITHARGSMOCK_H_ */
