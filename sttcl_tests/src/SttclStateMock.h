/*
 * SttclStateMock.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef STTCLSTATEMOCK_H_
#define STTCLSTATEMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestStateInterface.h"
#include "IStateMachineHooks.h"
#include "IStateHooks.h"
#include "SttclTestLog.h"

class SttclStateMachineMock;

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class SttclStateMock
: public sttcl::State<SttclStateMock,SttclStateMachineMock,ITestStateInterface>
, public IStateHooks
{
public:
	typedef sttcl::State<SttclStateMock,SttclStateMachineMock,ITestStateInterface> StateBaseClass;

	SttclStateMock(const std::string& stateId = "<anonymous>")
	: StateBaseClass(&SttclStateMock::doActionImplCall)
	, stateId_(stateId)
	, directTransitState_(NULL)
	, finalizeOnNextDirectTransitCheck_(false)
	, enableLogs_(false)
	{
		ON_CALL(*this, handleEvent1(_))
			.WillByDefault(Invoke(this, &SttclStateMock::handleEvent1Call));
		ON_CALL(*this, handleEvent2(_))
			.WillByDefault(Invoke(this, &SttclStateMock::handleEvent2Call));
		ON_CALL(*this, handleEvent3(_))
			.WillByDefault(Invoke(this, &SttclStateMock::handleEvent3Call));
		ON_CALL(*this, handleEvent4(_))
			.WillByDefault(Invoke(this, &SttclStateMock::handleEvent4Call));

		ON_CALL(*this, entryImpl(_))
			.WillByDefault(Invoke(this, &SttclStateMock::entryImplCall));
		ON_CALL(*this, exitImpl(_))
			.WillByDefault(Invoke(this, &SttclStateMock::exitImplCall));
		ON_CALL(*this, startDoImpl(_))
			.WillByDefault(Invoke(this, &SttclStateMock::startDoImplCall));
		ON_CALL(*this, endDoImpl(_))
			.WillByDefault(Invoke(this, &SttclStateMock::endDoImplCall));
		ON_CALL(*this, finalizeSubStateMachinesImpl(_))
			.WillByDefault(Invoke(this, &SttclStateMock::finalizeSubStateMachinesImplCall));
		ON_CALL(*this, initSubStateMachinesImpl(_))
			.WillByDefault(Invoke(this, &SttclStateMock::initSubStateMachinesImplCall));
		ON_CALL(*this, checkDirectTransitionImpl(_,_,_))
			.WillByDefault(Invoke(this, &SttclStateMock::checkDirectTransitionImplCall));
		ON_CALL(*this, doActionImpl(_,_))
			.WillByDefault(Invoke(this, &SttclStateMock::doActionImplCall));
        ON_CALL(*this, joinDoActionImpl(_))
            .WillByDefault(Invoke(this, &SttclStateMock::joinDoActionImplCall));
	}

	virtual ~SttclStateMock() {}

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
			STTCL_TEST_LOG(id() << " Calling SttclStateMock::StateBaseClass::entryImpl( context = " << context << ") ...");
		}
		StateBaseClass::entryImpl(context);
	}

	void exitImplCall(SttclStateMachineMock* context)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclStateMock::StateBaseClass::exitImpl( context = " << context << ") ...");
		}
		StateBaseClass::exitImpl(context);
	}

	void startDoImplCall(SttclStateMachineMock* context)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclStateMock::StateBaseClass::startDoImpl( context = " << context << ") ...");
		}
		StateBaseClass::startDoImpl(context);
	}

	void endDoImplCall(SttclStateMachineMock* context)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclStateMock::StateBaseClass::endDoImpl( context = " << context << ") ...");
		}
		StateBaseClass::endDoImpl(context);
	}

	void finalizeSubStateMachinesImplCall(bool recursive)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclStateMock::StateBaseClass::finalizeSubStateMachinesImpl(" << recursive << ") ...");
		}
		StateBaseClass::finalizeSubStateMachinesImpl(recursive);
	}

	void initSubStateMachinesImplCall(bool recursive)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclStateMock::StateBaseClass::initSubStateMachinesImpl(" << recursive << ") ...");
		}
		StateBaseClass::initSubStateMachinesImpl(recursive);
	}

	bool checkDirectTransitionImplCall(SttclStateMachineMock* context, bool& finalize, sttcl::StateBase<SttclStateMachineMock,ITestStateInterface>*& nextState)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclStateMock::StateBaseClass::checkDirectTransitionImpl( context = " << context << ", finalize = " << finalize << ", nextState = " << nextState << ") ...");
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

	void doActionImplCall(SttclStateMachineMock* context, bool firstCall)
	{
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " SttclStateMock::doActionImplCall( context = " << context << ", firstCall = " << firstCall);
		}
	}

    void joinDoActionImplCall(SttclStateMachineMock* context)
    {
        if(enableLogs_)
        {
            STTCL_TEST_LOG(id() << " Calling SttclStateMock::StateBaseClass::joinDoActionImpl(" << context << ") ...");
        }
        StateBaseClass::joinDoActionImpl(context);
    }

    std::string stateId_;
	mutable sttcl::internal::SttclMutex<> internalGuard_;
	StateBaseClass::StateBaseType* directTransitState_;
	bool finalizeOnNextDirectTransitCheck_;
	bool enableLogs_;
};


#endif /* STTCLSTATEMOCK_H_ */
