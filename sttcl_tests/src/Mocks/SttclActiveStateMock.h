/*
 * SttclActiveStateMock.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef STTCLACTIVESTATEMOCK_H_
#define STTCLACTIVESTATEMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <ActiveState.h>
#include <SttclMutex.h>
#include <SttclSemaphore.h>
#include <SttclTime.h>
#include "ITestStateInterface.h"
#include "IStateMachineHooks.h"
#include "IActiveStateHooks.h"
#include "SttclTestLog.h"
#include <unistd.h>

class SttclStateMachineMock;

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class SttclActiveStateMock
: public sttcl::ActiveState<SttclActiveStateMock,SttclStateMachineMock,ITestStateInterface>
, public IActiveStateHooks<SttclStateMachineMock>
{
public:
	typedef sttcl::ActiveState<SttclActiveStateMock,SttclStateMachineMock,ITestStateInterface> StateBaseClass;

	SttclActiveStateMock(const std::string& stateId = "<anonymous>", sttcl::TimeDuration<> doFrequency = sttcl::TimeDuration<>(0,0,0,100))
	: StateBaseClass(&SttclActiveStateMock::doActionImplCall,false,doFrequency)
	, directTransitState_(NULL)
	, finalizeOnNextDirectTransitCheck_(false)
	, enableLogs_(false)
	, stateId_(stateId)
	//, doActionExitedSema(0)
	, doActionExited(true)
	{
		ON_CALL(*this, handleEvent1(_))
			.WillByDefault(Invoke(this, &SttclActiveStateMock::handleEvent1Call));
		ON_CALL(*this, handleEvent2(_))
			.WillByDefault(Invoke(this, &SttclActiveStateMock::handleEvent2Call));
		ON_CALL(*this, handleEvent3(_))
			.WillByDefault(Invoke(this, &SttclActiveStateMock::handleEvent3Call));
		ON_CALL(*this, handleEvent4(_))
			.WillByDefault(Invoke(this, &SttclActiveStateMock::handleEvent4Call));

		ON_CALL(*this, entryImpl(_))
			.WillByDefault(Invoke(this, &SttclActiveStateMock::entryImplCall));
		ON_CALL(*this, exitImpl(_))
			.WillByDefault(Invoke(this, &SttclActiveStateMock::exitImplCall));
		ON_CALL(*this, startDoImpl(_))
			.WillByDefault(Invoke(this, &SttclActiveStateMock::startDoImplCall));
		ON_CALL(*this, endDoImpl(_))
			.WillByDefault(Invoke(this, &SttclActiveStateMock::endDoImplCall));
		ON_CALL(*this, finalizeSubStateMachinesImpl(_))
			.WillByDefault(Invoke(this, &SttclActiveStateMock::finalizeSubStateMachinesImplCall));
		ON_CALL(*this, initSubStateMachinesImpl(_))
			.WillByDefault(Invoke(this, &SttclActiveStateMock::initSubStateMachinesImplCall));
		ON_CALL(*this, checkDirectTransitionImpl(_,_,_))
			.WillByDefault(Invoke(this, &SttclActiveStateMock::checkDirectTransitionImplCall));
		ON_CALL(*this, doActionImpl(_,_))
			.WillByDefault(Invoke(this, &SttclActiveStateMock::doActionImplCall));
        ON_CALL(*this, joinDoActionImpl(_))
            .WillByDefault(Invoke(this, &SttclActiveStateMock::joinDoActionImplCall));

		ON_CALL(*this, exitingDoActionImpl())
			.WillByDefault(Invoke(this, &SttclActiveStateMock::exitingDoActionImplCall));
		ON_CALL(*this, joinDoActionThreadImpl())
			.WillByDefault(Invoke(this, &SttclActiveStateMock::joinDoActionThreadImplCall));
		ON_CALL(*this, unblockDoActionImpl())
			.WillByDefault(Invoke(this, &SttclActiveStateMock::unblockDoActionImplCall));
	}

	virtual ~SttclActiveStateMock() {}

	const std::string& id() const { return stateId_; }
	void setDirectTransitState(StateBaseClass::StateBaseType* directTransitState)
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

	void enableLogs(bool enable)
	{
		enableLogs_ = enable;
	}

	bool waitForDoActionExited(const sttcl::TimeDuration<>& checkFrequency, int retries = 1)
	{
	    do
	    {
            if(doActionExited)
            {
                return true;
            }
            sttcl::internal::SttclThread<>::sleep(checkFrequency);
            --retries;
	    } while(retries > 0);
	    return false;
	}
	MOCK_METHOD1(handleEvent1, void (SttclStateMachineMock* context));
	MOCK_METHOD1(handleEvent2, void (SttclStateMachineMock* context));
	MOCK_METHOD1(handleEvent3, void (SttclStateMachineMock* context));
	MOCK_METHOD1(handleEvent4, void (SttclStateMachineMock* context));

	MOCK_METHOD1(entryImpl, void (SttclStateMachineMock* context));
	MOCK_METHOD1(exitImpl, void (SttclStateMachineMock* context));
	MOCK_METHOD1(startDoImpl, void (SttclStateMachineMock* context));
	MOCK_METHOD1(endDoImpl, void (SttclStateMachineMock* context));
	MOCK_METHOD1(finalizeSubStateMachinesImpl, void (bool recursive));
	MOCK_METHOD1(initSubStateMachinesImpl, void (bool recursive));
	MOCK_METHOD3(checkDirectTransitionImpl, bool (SttclStateMachineMock* context, bool& finalize, sttcl::StateBase<SttclStateMachineMock,ITestStateInterface>*& nextState));
	MOCK_METHOD2(doActionImpl, void (SttclStateMachineMock* context, bool firstCall));
    MOCK_METHOD1(joinDoActionImpl, void (SttclStateMachineMock* context));

	MOCK_METHOD0(exitingDoActionImpl, void ());
	MOCK_METHOD0(joinDoActionThreadImpl, void ());
	MOCK_METHOD0(unblockDoActionImpl, void ());

protected:
	void handleEvent1Call(SttclStateMachineMock* context)
	{

	}

	void handleEvent2Call(SttclStateMachineMock* context)
	{

	}

	void handleEvent3Call(SttclStateMachineMock* context)
	{

	}

	void handleEvent4Call(SttclStateMachineMock* context)
	{

	}

	void entryImplCall(SttclStateMachineMock* context)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclActiveStateMock::StateBaseClass::entryImpl( context = " << context << ") ...");
		}
		StateBaseClass::entryImpl(context);
	}

	void exitImplCall(SttclStateMachineMock* context)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclActiveStateMock::StateBaseClass::exitImpl( context = " << context << ") ...");
		}
		StateBaseClass::exitImpl(context);
	}

	void startDoImplCall(SttclStateMachineMock* context)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclActiveStateMock::StateBaseClass::startDoImpl( context = " << context << ") ...");
		}
		StateBaseClass::startDoImpl(context);
        { sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalLockGuard);
            doActionExited = false;
        }
	}

	void endDoImplCall(SttclStateMachineMock* context)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclActiveStateMock::StateBaseClass::endDoImpl( context = " << context << ") ...");
		}
		StateBaseClass::endDoImpl(context);
	}

	void finalizeSubStateMachinesImplCall(bool recursive)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclActiveStateMock::StateBaseClass::finalizeSubStateMachinesImpl(" << recursive << ") ...");
		}
		StateBaseClass::finalizeSubStateMachinesImpl(recursive);
	}

	void initSubStateMachinesImplCall(bool recursive)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclActiveStateMock::StateBaseClass::initSubStateMachinesImpl(" << recursive << ") ...");
		}
		StateBaseClass::initSubStateMachinesImpl(recursive);
	}

	bool checkDirectTransitionImplCall(SttclStateMachineMock* context, bool& finalize, sttcl::StateBase<SttclStateMachineMock,ITestStateInterface>*& nextState)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclActiveStateMock::StateBaseClass::checkDirectTransitionImpl( context = " << context << ", finalize = " << finalize << ", nextState = " << nextState << ") ...");
		}
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
				finalize = true;
				return true;
			}

		}
		return false;
	}

	void doActionImplCall(SttclStateMachineMock* context, bool firstCall)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " SttclActiveStateMock::doActionImplCall( context = " << context << ", firstCall = " << firstCall);
		}
	}

    void exitingDoActionImplCall()
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclActiveStateMock::StateBaseClass::exitingDoActionImplCall() ...");
		}
		StateBaseClass::exitingDoActionImpl();
		//doActionExitedSema.post();

		{ sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalLockGuard);
		    doActionExited = true;
		}
    }

    void joinDoActionThreadImplCall()
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclActiveStateMock::StateBaseClass::joinDoActionThreadImpl() ...");
		}
		StateBaseClass::joinDoActionThreadImpl();
    }

    void joinDoActionImplCall(SttclStateMachineMock* context)
    {
        if(enableLogs_)
        {
            STTCL_TEST_LOG(id() << " Calling SttclActiveStateMock::StateBaseClass::joinDoActionImpl(" << context << ") ...");
        }
        StateBaseClass::joinDoActionImpl(context);
    }

    void unblockDoActionImplCall()
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << "  Calling SttclActiveStateMock::StateBaseClass::unblockDoActionImpl() ...");
		}
		StateBaseClass::unblockDoActionImpl();
    }

	mutable sttcl::internal::SttclMutex<> internalGuard_;
	StateBaseClass::StateBaseType* directTransitState_;
	bool finalizeOnNextDirectTransitCheck_;
	bool enableLogs_;
	std::string stateId_;
	sttcl::internal::SttclMutex<> internalLockGuard;
	bool doActionExited;
	//sttcl::internal::SttclSemaphore<> doActionExitedSema;

};

#endif /* STTCLACTIVESTATEMOCK_H_ */
