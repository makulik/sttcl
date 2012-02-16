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
, class TimeDurationType
, class ActiveStateMutexType
>
class ActiveState;

/**
 * Helper class to call a state thread method.
 */
struct ThreadFunctionHelper
{
	/**
	 * Defines a static method that can be passed to a thread implementation.
	 * @tparam StateImpl The \link sttcl::ActiveState\endlink<>
	 *                   implementation class.
	 * @tparam StateMachineImpl The \link sttcl::StateMachine\endlink<> implementation
	 *                          class that contains the \link sttcl::ActiveState\endlink<>
	 *                          implementation.
	 * @tparam IState The inner event handler interface of the
	 *                \link sttcl::StateMachine\endlink<> implementation
	 * @tparam StateThreadType The thread implementation class, default is
	 *                         \link sttcl::SttclThread\endlink<>.
	 * @tparam EndDoActionSemaphoreType The semaphore implementation class, default is
	 *                                  \link sttcl::SttclSemaphore\endlink<>.
	 * @tparam TimeDurationType The time duration representation implementation class, default
	 *                          is \link sttcl::TimeDuration\endlink<>.
	 * @tparam ActiveStateMutexType The mutex implementation class, default
	 *                              is \link sttcl::SttclMutex\endlink<>.
	 * @param args A pointer to the thread args. Implicitely \em args is casted to
	 *             \link sttcl::ActiveState\endlink<> and the
	 *             \link sttcl::ActiveState::runDoAction\endlink method is called.
	 */
	template
	< class StateImpl
	, class StateMachineImpl
	, class IState
	, class StateThreadType
	, class EndDoActionSemaphoreType
	, class TimeDurationType
	, class ActiveStateMutexType
	>
    static void* stateThreadMethod(void* args)
    {
    	ActiveState<StateImpl
    	           ,StateMachineImpl
    	           ,IState
    	           ,StateThreadType
    	           ,EndDoActionSemaphoreType
    	           ,TimeDurationType
    	           ,ActiveStateMutexType
    	           >* pThis =
    			reinterpret_cast<ActiveState<StateImpl
    			                            ,StateMachineImpl
    			                            ,IState
    			                            ,StateThreadType
    			                            ,EndDoActionSemaphoreType
    			                            ,TimeDurationType
    			                            ,ActiveStateMutexType
    			                            >*>(args);
    	pThis->runDoAction(pThis->currentContext);
    	return 0;
    }
};

/**
 * Represents a particular state machines active state implementation base class.
 * An ActiveState implementation runs its do action in a separate thread.
 *
 * @tparam StateImpl The state implementation type.
 * @tparam StateMachineImpl The state machine implementation type.
 * @tparam IState Specifies the internal interface of state implementations for the state
 *                machine.
 * @tparam StateThreadType The thread implementation class, default is
 *                         \link sttcl::SttclThread\endlink<>.
 * @tparam EndDoActionSemaphoreType The semaphore implementation class, default is
 *                                  \link sttcl::SttclSemaphore\endlink<>.
 * @tparam TimeDurationType The time duration representation implementation class, default
 *                          is \link sttcl::TimeDuration\endlink<>.
 * @tparam ActiveStateMutexType The mutex implementation class, default
 *                              is \link sttcl::SttclMutex\endlink<>.
 */
template
< class StateImpl
, class StateMachineImpl
, class IState
, class StateThreadType = SttclThread<>
, class EndDoActionSemaphoreType = SttclSemaphore<>
, class TimeDurationType = TimeDuration<>
, class ActiveStateMutexType = SttclMutex<>
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
     * The state base class type.
     */
    typedef StateBase<StateMachineImpl,IState> StateBaseType;

    /**
     * The state do action type.
     */
    typedef void (Implementation::*StateDoAction)(Context*, bool);

    /**
     * The thread class type.
     */
    typedef StateThreadType StateThreadImpl;

    /**
     * The semaphore class type to use for ending the do action call loop.
     */
    typedef EndDoActionSemaphoreType EndDoActionSemaphoreImpl;

    /**
     * The time duration class type to use for specifying the do action call rate.
     */
    typedef TimeDurationType TimeDurationImpl;

    /**
     * The mutex class type to use for co9ordinating access to ActiveState internal variables.
     */
    typedef ActiveStateMutexType ActiveStateMutexImpl;

    /**
     * Gets the do action call frequency.
     */
    inline const TimeDurationImpl& getDoFrequency() const
	{
    	return doFrequency;
	}

    /**
     * Sets the do action call frequency.
     */
    inline void setDoFrequency(const TimeDurationImpl& newValue)
	{
    	doFrequency = newValue;
	}

    /**
     * Default implementation for checking if endDo() was requested.
     * @return \c true if the do action loop should be left, \c false otherwise.
     */
    bool endDoActionRequestedImpl()
    {
		bool result = endDoActionSemaphore.try_wait(doFrequency);
		return result;
    }

    /**
     * Default implementation for the entry() method.
     * @param context A pointer to the containing state machine.
     */
    inline void entryImpl(Context* context)
    {
    }

    /**
     * Default implementation for the exit() method.
     * @param context A pointer to the containing state machine.
     */
    inline void exitImpl(Context* context)
    {

    }


    /**
     * Default implementation for the exitingDoActionImpl() method.
     * The method is called when the do action thread is exiting.
     */
    inline void exitingDoActionImpl()
    {
    }

    /**
     * Default implementation to join the active state thread.
     */
    inline void joinDoActionThreadImpl()
    {
    	if(!StateThreadType::isSelf(stateThread))
    	{
    		stateThread.join();
    	}
    }

    /**
     * Default implementation called to unblock any blocking methods waiting in the do action
     * call.
     */
    inline void unblockDoActionImpl()
    {
    }

    /**
     * ActiveState class default implementation for the endDo() method.
     * @param context A pointer to the containing state machine.
     */
    inline void endDoImpl(Context* context)
    {
    	if(!StateThreadType::isSelf(stateThread))
    	{
    		endDoActionSemaphore.post();
    		if(isDoActionRunning())
    		{
    			static_cast<StateImpl*>(this)->unblockDoActionImpl();
    		}
			static_cast<Implementation*>(this)->joinDoActionThreadImpl();
			currentContext = 0;
    	}
    }

    /**
     * Gets the thread instance used to run the ActiveState do action.
     * @return
     */
    inline const StateThreadType& getStateThread() const
    {
    	return stateThread;
    }

    /**
     * Called after this state was entered.
     *
     * @param context The state machine context.
     */
    inline void startDoImpl(Context* context)
    {
//        if(doAction)
//        {
			currentContext = context;
        	stateThread.run(this);
//        }
    }

    inline bool isDoActionRunning() const
    {
		AutoLocker<ActiveStateMutexType> lock(activeStateMutex);
		return doActionRunning;
    }

    /**
     * Default implementation for the finalizeSubStateMachines() method.
     * @param recursive If \c true further sub state machines should be finalized
     *                  recursively.
     */
    void finalizeSubStateMachinesImpl(bool recursive)
    {
    }

    /**
     * Default implementation for the initSubStateMachines() method.
     * @param recursive If \c true further sub state machines should be initialized
     *                  recursively.
     */
    void initSubStateMachinesImpl(bool recursive)
    {
    }

    /**
     * Default implementation for the getDirectTransitionImpl() method.
     * @param context A pointer to the containing state machine.
     * @param nextState Receives a pointer to the next sibling state to appear on a direct transition.
     * @param finalize Receives \c true to finalize the containing state machine.
     * @return \c true if a direct transition should be performed, \c false otherwise.
     */
    bool checkDirectTransitionImpl(Context* context, bool& finalize, StateBaseType*& nextState)
    {
    	nextState = 0;
    	finalize = false;
    	return false;
    }

protected:
	/**
     * Constructor for class ActiveState.
	 * @param argDoAction The do action that will be called in the ActiveState's thread.
	 * @param argRunDoActionOnce Indicates to run the do action only once after the state was
	 *                           entered.
	 * @param argDoFrequency The frequency used to call the do action in a loop. You can use this
	 *                       to limit the CPU resources given to the do action. If the do action
	 *                       uses another blocking mechanism the parameter may be omitted (the
	 *                       default is TimeDurationType::Zero).
	 */
    ActiveState(StateDoAction argDoAction, bool argRunDoActionOnce = false , TimeDuration<> argDoFrequency = TimeDuration<>::Zero)
    : doAction(argDoAction)
    , doFrequency(argDoFrequency)
    , currentContext(0)
    , stateThread(&ThreadFunctionHelper::stateThreadMethod
					< StateImpl
					, StateMachineImpl
					, IState
					, StateThreadType
					, EndDoActionSemaphoreType
					, TimeDurationType
					, ActiveStateMutexType>)
    , endDoActionSemaphore(0)
    , doActionRunning(false)
    , runDoActionOnce(argRunDoActionOnce)
    {
    }

    /**
     * Destructor for class ActiveState.
     */
    virtual ~ActiveState()
    {
    	if(isDoActionRunning())
    	{
    		endDo(currentContext);
    	}
    }

    /**
     * Changes \em context state machine to another sibling state.
     * @param context A pointer to the containing state machine.
     * @param newState A pointer to the sibling state to change to.
     */
    void changeState(Context* context,StateBase<StateMachineImpl,IState>* newState)
    {
    	static_cast<Implementation*>(this)->changeStateImpl(context,newState);
    }

    /**
     * Indicates that the do action thread should stop.
     * @return \c true if the do action thread should stop, \c false otherwise.
     */
    bool endDoActionRequested()
    {
    	return static_cast<Implementation*>(this)->endDoActionRequestedImpl();
    }

private:
    virtual void entry(Context* context)
    {
        static_cast<Implementation*>(this)->entryImpl(context);
    }

    virtual void exit(Context* context)
    {
        static_cast<Implementation*>(this)->exitImpl(context);
    }

    virtual void startDo(Context* context)
    {
        static_cast<Implementation*>(this)->startDoImpl(context);
    }

    virtual void endDo(Context* context)
    {
        static_cast<Implementation*>(this)->endDoImpl(context);
    }

    void setDoActionRunning(bool value)
    {
		AutoLocker<ActiveStateMutexType> lock(activeStateMutex);
		doActionRunning = value;
    }

    void runDoAction(Context* context)
    {
    	bool initialCall = true;
    	setDoActionRunning(true);
    	bool directTransitionTriggered = false;
    	do
    	{
    		// Run the do action
    		if(doAction)
    		{
				(static_cast<Implementation*>(this)->*doAction)(context,initialCall);
				if(initialCall)
				{
					initialCall = false;
				}
    		}

            // Handle direct transitions
            StateBaseType* nextState = 0;
            bool finalize = false;
            if(static_cast<Implementation*>(this)->checkDirectTransitionImpl(context,finalize,nextState))
    		{
    			if(finalize)
    			{
    				context->finalize();
    			}
    			else if(nextState)
    			{
    				changeState(context,nextState);
    				directTransitionTriggered = true;
    			}
    		}
    	} while(!endDoActionRequested() && !runDoActionOnce && !directTransitionTriggered);
        static_cast<Implementation*>(this)->exitingDoActionImpl();
    	setDoActionRunning(false);
    }

    virtual void finalizeSubStateMachines(bool recursive)
    {
        static_cast<Implementation*>(this)->finalizeSubStateMachinesImpl(recursive);
    }

    virtual void initSubStateMachines(bool recursive)
    {
        static_cast<Implementation*>(this)->initSubStateMachinesImpl(recursive);
    }

    StateDoAction doAction;
    TimeDuration<> doFrequency;
    Context* currentContext;
    StateThreadType stateThread;
    EndDoActionSemaphoreType endDoActionSemaphore;
    mutable ActiveStateMutexType activeStateMutex;
	bool doActionRunning;
	bool runDoActionOnce;
};

}

#endif /* ACTIVESTATE_H_ */
