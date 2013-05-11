/*
 * SttclRegionWithArgsMock.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef STTCLREGIONWITHARGSMOCK_H_
#define STTCLREGIONWITHARGSMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <Region.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestStateInterfaceWithArgs.h"
#include "ITestInnerStateInterfaceWithArgs.h"
#include "IRegionWithArgsHooks.h"
#include "SttclTestLog.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template
    < class RegionImpl
    , class RegionContainer
    , class InnerStateInterface
    >
class SttclRegionWithArgsMock
: public sttcl::Region<RegionImpl,RegionContainer,InnerStateInterface,EventArgs>
, public IRegionWithArgsHooks<RegionImpl,RegionContainer,InnerStateInterface>
{
public:

	typedef sttcl::Region<RegionImpl,RegionContainer,InnerStateInterface,EventArgs> RegionBaseClass;
    typedef typename RegionBaseClass::StateImplementationBase StateBaseClass;
    typedef typename RegionBaseClass::InnerStateClass InnerStateClass;

	SttclRegionWithArgsMock
	    ( const std::string& stateMachineId
        , RegionContainer* regionContainer
	    , InnerStateClass* initialState = NULL
	    , sttcl::TimeDuration<> argDoActionFrequency = sttcl::TimeDuration<>(0,0,0,10)
	    )
	: RegionBaseClass(regionContainer,argDoActionFrequency)
    , initialState_(initialState)
	, enableLogs_(false)
	, stateMachineId_(stateMachineId)
    , doActionThreadExited_(0)
	{
		ON_CALL(*this, initializeImpl(_))
			.WillByDefault(Invoke(this, &SttclRegionWithArgsMock::initializeImplCall));
		ON_CALL(*this, finalizeImpl(_))
			.WillByDefault(Invoke(this, &SttclRegionWithArgsMock::finalizeImplCall));
		ON_CALL(*this, subStateMachineCompleted())
			.WillByDefault(Invoke(this, &SttclRegionWithArgsMock::subStateMachineCompletedCall));
        ON_CALL(*this, subStateMachineCompletedImpl())
            .WillByDefault(Invoke(this, &SttclRegionWithArgsMock::subStateMachineCompletedImplCall0));
		ON_CALL(*this, getInitialStateImpl())
			.WillByDefault(Invoke((const SttclRegionWithArgsMock*)this, &SttclRegionWithArgsMock::getInitialStateImplCall));
		ON_CALL(*this, isReadyImpl())
			.WillByDefault(Invoke((const SttclRegionWithArgsMock*)this, &SttclRegionWithArgsMock::isReadyImplCall));

        ON_CALL(*this, enterRegionImpl(_))
            .WillByDefault(Invoke(this, &SttclRegionWithArgsMock::enterRegionImplCall));
        ON_CALL(*this, exitRegionImpl(_))
            .WillByDefault(Invoke(this, &SttclRegionWithArgsMock::exitRegionImplCall));
        ON_CALL(*this, startingRegionThread())
            .WillByDefault(Invoke(this, &SttclRegionWithArgsMock::startingRegionThreadCall));
        ON_CALL(*this, endingRegionThread())
            .WillByDefault(Invoke(this, &SttclRegionWithArgsMock::endingRegionThreadCall));
	}

	virtual ~SttclRegionWithArgsMock()
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

    // IRegionWithArgsHooks
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

    bool waitForDoActionExited(const sttcl::TimeDuration<>& timeout)
    {
        if(!doActionThreadExited_.try_wait(timeout))
        {
            finalizeImpl(true);
            return false;
        }
        return true;
    }

protected:
	mutable sttcl::internal::SttclMutex<> internalGuard_;
	InnerStateClass* initialState_;
    bool enableLogs_;
    std::string stateMachineId_;
    sttcl::internal::SttclSemaphore<> doActionThreadExited_;

private:
	bool isReadyImplCall() const
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClass::isReadyImpl() ...");
    	return SttclRegionWithArgsMock::RegionBaseClass::isReadyImpl();
    }

    bool initializeImplCall(bool force)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClass::initializeImpl(" << force << ") ...");
    	return RegionBaseClass::initializeImpl(force);
    }

    void finalizeImplCall(bool finalizeSubStateMachines)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClass::finalizeImpl(" << finalizeSubStateMachines << ") ...");
		RegionBaseClass::finalizeImpl(finalizeSubStateMachines);
    }

    void subStateMachineCompletedCall()
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClass::subStateMachineCompleted() ...");
        RegionBaseClass::subStateMachineCompleted();
    }

    void subStateMachineCompletedImplCall0()
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClass::subStateMachineCompletedImpl() ...");
        RegionBaseClass::subStateMachineCompletedImpl();
    }

    void subStateMachineCompletedImplCall1(IStateMachineWithArgsHooks<ITestInnerStateInterfaceWithArgs>::StateBaseClass* state)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClass::subStateMachineCompletedImpl() ...");
        RegionBaseClass::subStateMachineCompleted();
    }

    InnerStateClass* getInitialStateImplCall() const
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " SttclRegionWithArgsMock::getInitialStateImplCall(), initialState: = " << initialState_);
    	sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
    	return initialState_;
    }


    void enterRegionImplCall(RegionContainer* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClass::enterRegionImpl( context = " << context << ") ...");
        RegionBaseClass::enterRegionImpl(context);
    }

    void exitRegionImplCall(RegionContainer* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClass::exitRegionImpl( context = " << context << ") ...");
        RegionBaseClass::exitRegionImpl(context);
    }

    void startingRegionThreadCall()
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClass::startingRegionThread() ...");
        RegionBaseClass::startingRegionThread();
    }

    void endingRegionThreadCall()
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClass::endingRegionThread() ...");
        RegionBaseClass::endingRegionThread();
        doActionThreadExited_.post();
    }

};
#endif /* STTCLREGIONWITHARGSMOCK_H_ */
