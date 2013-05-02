/*
 * SttclRegionMock.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef STTCLREGIONMOCK_H_
#define STTCLREGIONMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <Region.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestStateInterface.h"
#include "ITestInnerStateInterface.h"
#include "IRegionHooks.h"
#include "SttclTestLog.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

template
    < class RegionImpl
    , class RegionContainer
    , class InnerStateInterface
    >
class SttclRegionMock
: public sttcl::Region<RegionImpl,RegionContainer,InnerStateInterface>
, public IRegionHooks<RegionImpl,RegionContainer,InnerStateInterface>
{
public:

	typedef sttcl::Region<RegionImpl,RegionContainer,InnerStateInterface> RegionBaseClass;
    typedef typename RegionBaseClass::StateImplementationBase StateBaseClass;
    typedef typename RegionBaseClass::InnerStateClass InnerStateClass;

	SttclRegionMock
	    ( const std::string& stateMachineId
        , RegionContainer* regionContainer
	    , InnerStateClass* initialState = NULL
	    , sttcl::TimeDuration<> argDoActionFrequency = sttcl::TimeDuration<>(0,0,0,10)
	    )
	: RegionBaseClass(regionContainer,argDoActionFrequency)
    , initialState_(initialState)
	, enableLogs_(false)
	, stateMachineId_(stateMachineId)
	{
		ON_CALL(*this, initializeImpl(_))
			.WillByDefault(Invoke(this, &SttclRegionMock::initializeImplCall));
		ON_CALL(*this, finalizeImpl(_))
			.WillByDefault(Invoke(this, &SttclRegionMock::finalizeImplCall));
		ON_CALL(*this, subStateMachineCompleted())
			.WillByDefault(Invoke(this, &SttclRegionMock::subStateMachineCompletedCall));
        ON_CALL(*this, subStateMachineCompletedImpl())
            .WillByDefault(Invoke(this, &SttclRegionMock::subStateMachineCompletedImplCall0));
		ON_CALL(*this, getInitialStateImpl())
			.WillByDefault(Invoke((const SttclRegionMock*)this, &SttclRegionMock::getInitialStateImplCall));
		ON_CALL(*this, isReadyImpl())
			.WillByDefault(Invoke((const SttclRegionMock*)this, &SttclRegionMock::isReadyImplCall));

        ON_CALL(*this, entryImpl(_))
            .WillByDefault(Invoke(this, &SttclRegionMock::entryImplCall));
        ON_CALL(*this, exitImpl(_))
            .WillByDefault(Invoke(this, &SttclRegionMock::exitImplCall));
        ON_CALL(*this, startDoImpl(_))
            .WillByDefault(Invoke(this, &SttclRegionMock::startDoImplCall));
        ON_CALL(*this, endDoImpl(_))
            .WillByDefault(Invoke(this, &SttclRegionMock::endDoImplCall));
        ON_CALL(*this, finalizeSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &SttclRegionMock::finalizeSubStateMachinesImplCall));
        ON_CALL(*this, initSubStateMachinesImpl(_))
            .WillByDefault(Invoke(this, &SttclRegionMock::initSubStateMachinesImplCall));
        ON_CALL(*this, doActionImpl(_,_))
            .WillByDefault(Invoke(this, &SttclRegionMock::doActionImplCall));
        ON_CALL(*this, joinDoActionThreadImpl())
            .WillByDefault(Invoke(this, &SttclRegionMock::joinDoActionThreadImplCall));
}

	virtual ~SttclRegionMock()
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

	// ITestStateInterface
    MOCK_METHOD1_T(handleEvent1, void (RegionContainer* context));
    MOCK_METHOD1_T(handleEvent2, void (RegionContainer* context));
    MOCK_METHOD1_T(handleEvent3, void (RegionContainer* context));
    MOCK_METHOD1_T(handleEvent4, void (RegionContainer* context));

    // IRegionHooks
    MOCK_CONST_METHOD0_T(getInitialStateImpl, InnerStateClass* ());
    MOCK_CONST_METHOD0(isReadyImpl, bool ());
	MOCK_METHOD1(initializeImpl, bool (bool force));
	MOCK_METHOD1(finalizeImpl,void (bool finalizeSubStateMachines));
    MOCK_METHOD0(subStateMachineCompleted, void ());
    MOCK_METHOD0(subStateMachineCompletedImpl, void ());

    MOCK_METHOD1_T(entryImpl, void (RegionContainer* context));
    MOCK_METHOD1_T(exitImpl, void (RegionContainer* context));
    MOCK_METHOD1_T(startDoImpl, void (RegionContainer* context));
    MOCK_METHOD1_T(endDoImpl, void (RegionContainer* context));
    MOCK_METHOD1(finalizeSubStateMachinesImpl, void (bool recursive));
    MOCK_METHOD1(initSubStateMachinesImpl, void (bool recursive));
    MOCK_METHOD2_T(doActionImpl, void (RegionContainer* context, bool firstCall));
    MOCK_METHOD0(joinDoActionThreadImpl, void ());


protected:
	mutable sttcl::internal::SttclMutex<> internalGuard_;
	InnerStateClass* initialState_;
    bool enableLogs_;
    std::string stateMachineId_;

private:
	bool isReadyImplCall() const
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClassisReadyImpl() ...");
    	return SttclRegionMock::RegionBaseClass::isReadyImpl();
    }

    bool initializeImplCall(bool force)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClassinitializeImpl(" << force << ") ...");
    	return RegionBaseClass::initializeImpl(force);
    }

    void finalizeImplCall(bool finalizeSubStateMachines)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClassfinalizeImpl(" << finalizeSubStateMachines << ") ...");
		RegionBaseClass::finalizeImpl(finalizeSubStateMachines);
    }

    void subStateMachineCompletedCall()
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClasssubStateMachineCompleted() ...");
        RegionBaseClass::subStateMachineCompleted();
    }

    void subStateMachineCompletedImplCall0()
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClasssubStateMachineCompletedImpl() ...");
        RegionBaseClass::subStateMachineCompletedImpl();
    }

    void subStateMachineCompletedImplCall1(IStateMachineHooks<ITestInnerStateInterface>::StateBaseClass* state)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClasssubStateMachineCompletedImpl() ...");
        RegionBaseClass::subStateMachineCompleted();
    }

    InnerStateClass* getInitialStateImplCall() const
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " SttclRegionMock::getInitialStateImplCall(), initialState: = " << initialState_);
    	sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
    	return initialState_;
    }


    void entryImplCall(RegionContainer* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClass::entryImpl( context = " << context << ") ...");
        RegionBaseClass::entryImpl(context);
    }

    void exitImplCall(RegionContainer* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling RegionBaseClass::exitImpl( context = " << context << ") ...");
        RegionBaseClass::exitImpl(context);
    }

    void startDoImplCall(RegionContainer* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling StateMachineBaseClass::startDoImpl( context = " << context << ") ...");
        RegionBaseClass::startDoImpl(context);
    }

    void endDoImplCall(RegionContainer* context)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling StateMachineBaseClass::endDoImpl( context = " << context << ") ...");
        RegionBaseClass::endDoImpl(context);
    }

    void finalizeSubStateMachinesImplCall(bool recursive)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling StateMachineBaseClass::finalizeSubStateMachinesImpl(" << recursive << ") ...");
        RegionBaseClass::finalizeSubStateMachinesImpl(recursive);
    }

    void initSubStateMachinesImplCall(bool recursive)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling StateMachineBaseClass::initSubStateMachinesImpl(" << recursive << ") ...");
        RegionBaseClass::initSubStateMachinesImpl(recursive);
    }

    void doActionImplCall(RegionContainer* context, bool firstCall)
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " SttclRegionMock::doActionImplCall( context = " << context << ", firstCall = " << firstCall);
    }

    void joinDoActionThreadImplCall()
    {
        STTCL_TEST_LOG(logsEnabled(), id() << " Calling StateMachineBaseClass::joinDoActionThreadImpl() ...");
        RegionBaseClass::joinDoActionThreadImpl();
    }

};
#endif /* STTCLREGIONMOCK_H_ */
