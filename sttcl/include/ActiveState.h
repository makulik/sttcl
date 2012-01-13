/*
 * ActiveState.h
 *
 *  Created on: 14.12.2011
 *      Author: Admin
 */

#ifndef ACTIVESTATE_H_
#define ACTIVESTATE_H_

#include "State.h"
#include "SttclThread.h"
#include "SttclMutex.h"
#include "SttclSemaphore.h"
#include "SttclTime.h"

namespace sttcl
{

template
< class StateImpl
, class StateMachineImpl
, class IState
, class StateThreadType
, class EndDoActionSemaphoreType
>
class ActiveState;

struct ThreadFunctionHelper
{
	template
	< class StateImpl
	, class StateMachineImpl
	, class IState
	, class StateThreadType
	, class EndDoActionSemaphoreType
	>
    static void* stateThreadMethod(void* args)
    {
    	ActiveState<StateMachineImpl,StateImpl,IState,StateThreadType,EndDoActionSemaphoreType>* pThis =
    			reinterpret_cast<ActiveState<StateMachineImpl,StateImpl,IState,StateThreadType,EndDoActionSemaphoreType>*>(args);
    	pThis->runDoAction(pThis->currentContext);
    	return 0;
    }
};

/**
 * Represents a particular state machines active state implementation base class.
 *
 * @tparam StateImpl The state implementation type.
 * @tparam StateMachine The state machine implementation type.
 * @tparam IState Specifies the internal interface of state implementations for the state
 *                machine.
 */
template
< class StateImpl
, class StateMachineImpl
, class IState
, class StateThreadType = SttclThread<>
, class EndDoActionSemaphoreType = SttclSemaphore<>
>
class ActiveState
: public StateBase<StateMachineImpl,IState>
{
	friend class ThreadFunctionHelper;
public:
    /**
     * The state machine implementation type.
     */
    typedef StateMachineImpl Context;

    /**
     * The implementation class type.
     */
    typedef StateImpl Implementation;

    /**
     * The state do action type.
     */
    typedef void (Implementation::*StateDoAction)(Context*, bool);

    typedef StateThreadType StateThreadImpl;
    typedef EndDoActionSemaphoreType EndDoActionMutexImpl;

    const TimeDuration<>& getDoFrequency() const
	{
    	return doFrequency;
	}

    void setDoFrequency(const TimeDuration<>& newValue)
	{
    	doFrequency = newValue;
	}

    bool endDoActionRequestedImpl()
    {
		bool result = endDoActionSemaphore.try_wait(doFrequency);
		return result;
    }

    void exitingDoActionImpl()
    {
    }

    void joinDoActionThreadImpl()
    {
    	if(!StateThreadType::isSelf(stateThread))
    	{
    		stateThread.join();
    	}
    }

    void unblockDoActionImpl()
    {
    }

    void endDoImpl(Context* context)
    {
    	if(!StateThreadType::isSelf(stateThread))
    	{
    		endDoActionSemaphore.post();
    		if(isDoActionRunning())
    		{
    			static_cast<StateImpl*>(this)->unblockDoActionImpl();
    		}
    	}
		static_cast<Implementation*>(this)->joinDoActionThreadImpl();
		currentContext = 0;
    }

    const StateThreadType& getStateThread() const
    {
    	return stateThread;
    }

    /**
     * Called after this state was entered.
     *
     * @param context The state machine context.
     */
    virtual void startDoImpl(Context* context)
    {
        if(doAction)
        {
			currentContext = context;
        	stateThread.run(this);
        }
    }

    bool isDoActionRunning() const
    {
		AutoLocker<SttclMutex<> > lock(activeStateMutex);
		return doActionRunning;
    }

protected:
    /**
     * Constructor for class State.
     *
     * @param impl A pointer to the state implementation.
     */
    ActiveState(StateDoAction argDoAction, TimeDuration<> argDoFrequency = TimeDuration<>::Zero)
    : doAction(argDoAction)
    , doFrequency(argDoFrequency)
    , currentContext(0)
    , stateThread(&ThreadFunctionHelper::stateThreadMethod<StateMachineImpl,StateImpl,IState,StateThreadType,EndDoActionSemaphoreType>)
    , endDoActionSemaphore(0)
    , doActionRunning(false)
    {
    }

    virtual ~ActiveState()
    {
    	if(isDoActionRunning())
    	{
    		endDo(currentContext);
    	}
    }

    void changeState(Context* context,StateBase<StateMachineImpl,IState>* newState)
    {
    	changeStateImpl(context,newState);
    }

    bool endDoActionRequested()
    {
    	return static_cast<StateImpl*>(this)->endDoActionRequestedImpl();
    }

private:
    /**
     * Called when this state is entered.
     *
     * @param context The state machine context.
     */
    virtual void entry(Context* context)
    {
        static_cast<Implementation*>(this)->entryImpl(context);
    }

    /**
     * Called when this state is left.
     *
     * @param context The state machine context.
     */
    virtual void exit(Context* context)
    {
        static_cast<Implementation*>(this)->exitImpl(context);
    }

    /**
     * Called after this state was entered.
     *
     * @param context The state machine context.
     */
    virtual void startDo(Context* context)
    {
        static_cast<Implementation*>(this)->startDoImpl(context);
    }

    /**
     * Called before this state is left.
     *
     * @param context The state machine context.
     */
    virtual void endDo(Context* context)
    {
        static_cast<Implementation*>(this)->endDoImpl(context);
    }

    void setDoActionRunning(bool value)
    {
		AutoLocker<SttclMutex<> > lock(activeStateMutex);
		doActionRunning = value;
    }

    void runDoAction(Context* context)
    {
    	bool initialCall = true;
    	setDoActionRunning(true);
    	do
    	{
            (static_cast<Implementation*>(this)->*doAction)(context,initialCall);
            if(initialCall)
            {
            	initialCall = false;
            }
    	} while(!endDoActionRequested());
        static_cast<Implementation*>(this)->exitingDoActionImpl();
    	setDoActionRunning(false);
    }

    StateDoAction doAction;
    TimeDuration<> doFrequency;
    Context* currentContext;
    StateThreadType stateThread;
    EndDoActionSemaphoreType endDoActionSemaphore;
    mutable SttclMutex<> activeStateMutex;
	bool doActionRunning;
};

}

#endif /* ACTIVESTATE_H_ */
