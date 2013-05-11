/*
 * SttclStateMachineWithArgsMock.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef STTCLSTATEMACHINEMOCKWITHARGS_H_
#define STTCLSTATEMACHINEMOCKWITHARGS_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestStateInterfaceWithArgs.h"
#include "IStateMachineWithArgsHooks.h"
#include "SttclTestLog.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class SttclStateMachineWithArgsMock
: public sttcl::StateMachine<SttclStateMachineWithArgsMock,ITestStateInterfaceWithArgs>
, public IStateMachineWithArgsHooks<ITestStateInterfaceWithArgs>
{
public:

	typedef sttcl::StateMachine<SttclStateMachineWithArgsMock,ITestStateInterfaceWithArgs> StateMachineBaseClass;
	typedef IStateMachineWithArgsHooks<ITestStateInterfaceWithArgs>::StateBaseClass StateBaseClass;

	SttclStateMachineWithArgsMock(const std::string& stateMachineId = "<anonymous>", IStateMachineWithArgsHooks::StateBaseClass* initialState = NULL)
	: initialState_(initialState)
	, enableLogs_(false)
	, stateMachineId_(stateMachineId)
	{
		ON_CALL(*this, initializeImpl(_))
			.WillByDefault(Invoke(this, &SttclStateMachineWithArgsMock::initializeImplCall));
		ON_CALL(*this, finalizeImpl(_))
			.WillByDefault(Invoke(this, &SttclStateMachineWithArgsMock::finalizeImplCall));
		ON_CALL(*this, subStateMachineCompletedImpl(_))
			.WillByDefault(Invoke(this, &SttclStateMachineWithArgsMock::subStateMachineCompletedImplCall));
		ON_CALL(*this, getInitialStateImpl())
			.WillByDefault(Invoke((const SttclStateMachineWithArgsMock*)this, &SttclStateMachineWithArgsMock::getInitialStateImplCall));
		ON_CALL(*this, isReadyImpl())
			.WillByDefault(Invoke((const SttclStateMachineWithArgsMock*)this, &SttclStateMachineWithArgsMock::isReadyImplCall));
	}

	virtual ~SttclStateMachineWithArgsMock()
	{
//		finalize(true);
	}

	const std::string& id() const { return stateMachineId_; }
	void setInitialState(IStateMachineWithArgsHooks<ITestStateInterfaceWithArgs>::StateBaseClass* initialState)
	{
    	sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
		initialState_ = initialState;
	}

	void enableLogs(bool enable)
	{
		enableLogs_ = enable;
	}

    bool logsEnabled() const
    {
        return enableLogs_;
    }

	void triggerEvent1(int arg1, const std::string& arg2)
	{
	    StateBaseClass* currentState = getState();
	    if(currentState != NULL)
	    {
	        currentState->handleEvent1(this,arg1,arg2);
	    }
	}

    void triggerEvent2(double arg1)
    {
        StateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            currentState->handleEvent2(this, arg1);
        }
    }

    void triggerEvent3()
    {
        StateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            currentState->handleEvent3(this);
        }
    }

    void triggerEvent4(int arg1)
    {
        StateBaseClass* currentState = getState();
        if(currentState != NULL)
        {
            currentState->handleEvent4(this,arg1);
        }
    }

	MOCK_METHOD1(initializeImpl, bool (bool force));
	MOCK_METHOD1(finalizeImpl,void (bool finalizeSubStateMachines));
	MOCK_METHOD1(subStateMachineCompletedImpl, void (IStateMachineWithArgsHooks::StateBaseClass* state));
    MOCK_CONST_METHOD0(getInitialStateImpl, IStateMachineWithArgsHooks::StateBaseClass* ());
    MOCK_CONST_METHOD0(isReadyImpl, bool ());

protected:
	mutable sttcl::internal::SttclMutex<> internalGuard_;
	IStateMachineWithArgsHooks<ITestStateInterfaceWithArgs>::StateBaseClass* initialState_;
    bool enableLogs_;
    std::string stateMachineId_;

private:
	bool isReadyImplCall() const
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclStateMachineWithArgsMock::StateMachineBaseClass::isReadyImpl() ...");
		}
    	return SttclStateMachineWithArgsMock::StateMachineBaseClass::isReadyImpl();
    }

    bool initializeImplCall(bool force)
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclStateMachineWithArgsMock::StateMachineBaseClass::initializeImpl(" << force << ") ...");
		}
    	return SttclStateMachineWithArgsMock::StateMachineBaseClass::initializeImpl(force);
    }

    void finalizeImplCall(bool finalizeSubStateMachines)
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclStateMachineWithArgsMock::StateMachineBaseClass::finalizeImpl(" << finalizeSubStateMachines << ") ...");
		}
		SttclStateMachineWithArgsMock::StateMachineBaseClass::finalizeImpl(finalizeSubStateMachines);
    }

    void subStateMachineCompletedImplCall(IStateMachineWithArgsHooks<ITestStateInterfaceWithArgs>::StateBaseClass* state)
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(logsEnabled(), id() << " Calling SttclStateMachineWithArgsMock::StateMachineBaseClass::subStateMachineCompletedImpl(" << state << ") ...");
		}
    	SttclStateMachineWithArgsMock::StateMachineBaseClass::subStateMachineCompletedImpl(state);
    }

    IStateMachineWithArgsHooks::StateBaseClass* getInitialStateImplCall() const
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(logsEnabled(), id() << " SttclStateMachineWithArgsMock::getInitialStateImplCall(), initialState: = " << initialState_);
		}
    	sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
    	return initialState_;
    }

};
#endif /* STTCLSTATEMACHINEMOCKWITHARGS_H_ */
