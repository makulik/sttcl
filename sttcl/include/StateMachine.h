/**
 * @file StateMachine.h
 *
 * Copyright (c) 2012, Guenther Makulik All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 * the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *    disclaimer.
 * 2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided with the distribution.
 * 3) Neither the name STTCL nor the names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "SttclConfig.h"

#include "State.h"
#include <cassert>
#if defined(STTCL_DEBUG)
#include <iostream>
#if defined(STTCL_HAVE_RTTI)
#include <typeinfo>
#endif
#endif

#if defined(STTCL_USE_STL)
#include <set>
#endif

#if defined(STTCL_THREADSAFE_IMPL)
#include "SttclMutex.h"
#endif

namespace sttcl
{

/**
 * State machine flags bitfield.
 */
struct StateMachineFlags
{
    /**
     * Indicates that the state machine is initialized.
     */
    unsigned char initialized:1;
    /**
     * Indicates that the state machine is currently initializing.
     */
    unsigned char initializing:1;
    /**
     * Indicates that the state machine is finalized.
     */
    unsigned char finalized:1;
    /**
     * Indicates that the state machine is currently finalizing.
     */
    unsigned char finalizing:1;

    /**
     * Constructor for StateMachineFlags.
     */
    inline StateMachineFlags()
    : initialized(false)
    , initializing(false)
    , finalized(false)
    , finalizing(false)
    {
    }
};

/**
 * Represents the base class for a state machine.
 *
 * @tparam StateMachineImpl Specifies the class implementing the state machine.
 * @tparam IState Specifies the internal interface of state implementations for the state
 *                machine.
 */
template
	< class StateMachineImpl
	, class IState
#if defined(STTCL_THREADSAFE_IMPL)
	, class StateMachineMutexType = sttcl::internal::SttclMutex<STTCL_DEFAULT_MUTEXIMPL>
#endif
	>
class StateMachine
{

public:
#if defined(STTCL_THREADSAFE_IMPL)
    typedef StateMachineMutexType MutexType;
#endif
    /**
     * The state machine implementation type.
     */
    typedef StateMachineImpl Context;
    /**
     * The internal state implementation interface.
     */
    typedef IState StateInterface;
    /**
     * The internal state implementation base type.
     */
    typedef StateBase<StateMachineImpl,IState> StateBaseClass;

    friend class StateBase<StateMachineImpl,IState>;

    /**
     * Destructor for class StateMachine.
     */
    ~StateMachine()
    {
    	if(isInitialized() && !isFinalizing() && !isFinalized())
    	{
    		finalize();
    	}
    }

    /**
     * Initializes the state machine.
     * @param force Indicates to finalize the state machine before (re-)initializing.
     * @return The ready state of the state machine.
     */
    bool initialize(bool force = false)
    {
        bool result = static_cast<Context*>(this)->initializeImpl(force);
        return result;
    }

    /**
     * Finalizes the state machine.
     *
     * @param finalizeSubStateMachines Indicates to finalize any sub state machines.
     */
    void finalize(bool finalizeSubStateMachines = true)
    {
    	if(!isFinalized() && !isFinalizing())
    	{
    	    STTCL_STATEMACHINE_SAFESECTION_START(internalLockGuard);
                flags.finalizing = true;
            STTCL_STATEMACHINE_SAFESECTION_END;
			static_cast<Context*>(this)->finalizeImpl(finalizeSubStateMachines);
            STTCL_STATEMACHINE_SAFESECTION_START(internalLockGuard);
                flags.finalizing = false;
                flags.finalized = true;
            STTCL_STATEMACHINE_SAFESECTION_END;
    	}
    }

    /**
     * Indicates that the state machine is ready to process events.
     * @return \c true if the state machine is ready to process events, \c false otherwise.
     */
    inline bool isReady() const
    {
        return static_cast<const Context*>(this)->isReadyImpl();
    }

    /**
     * Default implementation for isReady().

     * @return \c true if the state machine is ready to process events, \c false otherwise.
     */
    inline bool isReadyImpl() const
    {
        STTCL_STATEMACHINE_SAFE_RETURN(internalLockGuard,flags.initialized && !flags.finalized);
    }

    /**
     * Indicates that the state machine is initialized.
     * @return \c true if the state machine is initialized, \c false otherwise.
     */
    bool isInitialized() const
    {
        STTCL_STATEMACHINE_SAFE_RETURN(internalLockGuard,flags.initialized);
    }

    /**
     * Indicates that the state machine is currently initializing.
     * @return \c true if the state machine is currently initializing, \c false otherwise.
     */
    bool isInitalizing() const
    {
        STTCL_STATEMACHINE_SAFE_RETURN(internalLockGuard,flags.initializing);
    }

    /**
     * Indicates that the state machine is finalized.
     * @return \c true if the state machine is finalized, \c false otherwise.
     */
    bool isFinalized() const
    {
        STTCL_STATEMACHINE_SAFE_RETURN(internalLockGuard,flags.finalized);
    }

    /**
     * Indicates that the state machine is currently finalizing.
     * @return \c true if the state machine is currently finalizing, \c false otherwise.
     */
    bool isFinalizing() const
    {
        STTCL_STATEMACHINE_SAFE_RETURN(internalLockGuard,flags.finalizing);
    }

    /**
     * Gets the current state.
     *
     * @return The current state.
     */
    inline StateBaseClass* getState() const
    {
        STTCL_STATEMACHINE_SAFE_RETURN(internalLockGuard,state);
    }

    /**
     * Default implementation for the initialize() method.
     * @param force Indicates to finalize the state machine before (re-)initializing.
     * @return The ready state of the state machine.
     */
    inline bool initializeImpl(bool force)
    {
        if(force || (!isInitialized() && !isInitalizing()))
        {
            STTCL_STATEMACHINE_SAFESECTION_START(internalLockGuard);
            flags.initializing = true;
            STTCL_STATEMACHINE_SAFESECTION_END;
            if(force)
            {
            	StateBaseClass* currentState = getState();
            	if(currentState)
            	{
            		currentState->finalizeSubStateMachines(true);
            	}
            	if(!isFinalized())
            	{
            		finalize(true);
            	}
            }

            StateBaseClass* initialState = getInitialState();
            if(initialState)
            {
				changeState(initialState);
            }
        	StateBaseClass* currentState = getState();
        	if(currentState)
        	{
        		currentState->initSubStateMachines(force);
        	}
            STTCL_STATEMACHINE_SAFESECTION_START(internalLockGuard);
                flags.initializing = false;
                flags.finalized = false;
                flags.initialized = true;
            STTCL_STATEMACHINE_SAFESECTION_END;
        }
        return isReady();
    }

    /**
     * Default implementation for the finalize() method.
     *
     * @param finalizeSubStateMachines Indicates to finalize any sub state machines.
     */
    inline void finalizeImpl(bool finalizeSubStateMachines)
    {
        if(state)
        {
            if(finalizeSubStateMachines)
            {
                state->finalizeSubStateMachines(true);
            }
            exitCurrentState();
        }
        setState(0);
        pickUpRunningActiveStates();
    }

    /**
     * Called by a contained (composite) state when its sub state machine is completed (finalized).
     * @param state A pointer to the contained (composite) state.
     */
    inline void subStateMachineCompleted(StateBaseClass* state)
    {
    	static_cast<StateMachineImpl*>(this)->subStateMachineCompletedImpl(state);
    }

    /**
     * The default implementation of the subStateMachineCompleted method.
     * @param state A pointer to the contained (composite) state.
     */
    inline void subStateMachineCompletedImpl(StateBaseClass* state)
    {
    }

    inline void registerActiveStateRunning(StateBaseClass* state)
    {
        STTCL_STATEMACHINE_SAFESECTION_START(internalLockGuard);
            if(activeStatesRunning.find(state) == activeStatesRunning.end())
            {
                activeStatesRunning.insert(state);
            }
        STTCL_STATEMACHINE_SAFESECTION_END;
    }

    inline void unregisterActiveStateRunning(StateBaseClass* state)
    {
        STTCL_STATEMACHINE_SAFESECTION_START(internalLockGuard);
            if(activeStatesRunning.find(state) != activeStatesRunning.end())
            {
                activeStatesRunning.erase(state);
            }
        STTCL_STATEMACHINE_SAFESECTION_END;
    }

    /**
     * Default implementation to set the state machine to \c isReady() conditions.
     */
    virtual void setReady()
    {
        static_cast<StateMachineImpl*>(this)->setReadyImpl();
    }

    /**
     * Default implementation to set the state machine to \c isReady() conditions.
     */
    inline void setReadyImpl()
    {
        STTCL_STATEMACHINE_SAFESECTION_START(internalLockGuard);
            flags.finalized = false;
            flags.initialized = true;
        STTCL_STATEMACHINE_SAFESECTION_END;
    }

protected:
    /**
     * Constructor for class StateMachine.
     */
    StateMachine()
    : state(0)
    , flags()
    {
    }

    /**
     * Changes the state machines current state.
     *
     * @param newState The new target state.
     */
#if defined(STTCL_THREADSAFE_IMPL)
    void changeState(typename StateMachine<StateMachineImpl,IState,StateMachineMutexType>::StateBaseClass* newState);
#else
    void changeState(typename StateMachine<StateMachineImpl,IState>::StateBaseClass* newState);
#endif

    /**
     * Sets the state machines current state without calling any state operations.
     * @param newState
     */
    inline void setState(StateBaseClass* newState)
    {
        STTCL_STATEMACHINE_SAFESECTION_START(internalLockGuard);
            state = newState;
        STTCL_STATEMACHINE_SAFESECTION_END;
    }

    /**
     * Gets the initial state of the state machine.
     *
     * @return The initial state of the state machine.
     */
    StateBaseClass* getInitialState() const
    {
    	StateBaseClass* result = static_cast<const Context*>(this)->getInitialStateImpl();
#if defined(STTCL_DEBUG) // && defined(STTCL_HAVE_RTTI)
    	if(!result)
    	{
    		std::cout << "WARNING: " << typeid(static_cast<const Context*>(this)).name() << ".getInitialStateImpl() returned NULL" << std::endl;
    	}
#endif
    	return result;
    }

    // Default implementations
    //---------------------------------------------------------------------------------------

    /**
     * Default implementation for getInitialState().
     *
     * @return The initial state of the state machine.
     */
    inline StateBaseClass* getInitialStateImpl() const
    {
        return 0;
    }

    void exitCurrentState();
    void enterNewState();

    void pickUpRunningActiveStates();

protected:
    StateBaseClass* state;

private:
    StateMachineFlags flags;
#if defined(STTCL_USE_STL)
    std::set<StateBaseClass*> activeStatesRunning;
#endif
#if defined(STTCL_THREADSAFE_IMPL)
    mutable StateMachineMutexType internalLockGuard;
#endif

};

#if defined(STTCL_THREADSAFE_IMPL)
template<class StateMachineImpl, class IState, class StateMachineMutexType>
void StateMachine<StateMachineImpl,IState,StateMachineMutexType>::changeState(typename StateMachine<StateMachineImpl,IState,StateMachineMutexType>::StateBaseClass* newState)
#else
template<class StateMachineImpl, class IState>
void StateMachine<StateMachineImpl,IState>::changeState(typename StateMachine<StateMachineImpl,IState>::StateBaseClass* newState)
#endif
{
    if(!isFinalizing())
    {
    	if(newState)
		{
			if(newState != state)
			{
				exitCurrentState();
				setState(newState);
				enterNewState();
			}
		}
		else // equivalent to finalize
		{
			finalize();
		}
    }
}

#if defined(STTCL_THREADSAFE_IMPL)
template
    < class StateMachineImpl
    , class IState
    , class StateMachineMutexType
    >
void StateMachine<StateMachineImpl,IState,StateMachineMutexType>::exitCurrentState()
{
    if(state)
    {
        state->endDo(static_cast<StateMachine<StateMachineImpl,IState,StateMachineMutexType>::Context*>(this));
        state->exit(static_cast<StateMachine<StateMachineImpl,IState,StateMachineMutexType>::Context*>(this));
    }
}
#else
template
    < class StateMachineImpl
    , class IState
    >
void StateMachine<StateMachineImpl,IState>::exitCurrentState()
{
    if(state)
    {
        state->endDo(static_cast<StateMachine<StateMachineImpl,IState>::Context*>(this));
        state->exit(static_cast<StateMachine<StateMachineImpl,IState>::Context*>(this));
    }
}
#endif

#if defined(STTCL_THREADSAFE_IMPL)
template
    < class StateMachineImpl
    , class IState
    , class StateMachineMutexType
    >
void StateMachine<StateMachineImpl,IState,StateMachineMutexType>::enterNewState()
{
    state->entry(static_cast<StateMachine<StateMachineImpl,IState,StateMachineMutexType>::Context*>(this));
    state->startDo(static_cast<StateMachine<StateMachineImpl,IState,StateMachineMutexType>::Context*>(this));
}
#else
template
    < class StateMachineImpl
    , class IState
    >
void StateMachine<StateMachineImpl,IState>::enterNewState()
{
    state->entry(static_cast<StateMachine<StateMachineImpl,IState>::Context*>(this));
    state->startDo(static_cast<StateMachine<StateMachineImpl,IState>::Context*>(this));
}
#endif

#if defined(STTCL_THREADSAFE_IMPL)
template
    < class StateMachineImpl
    , class IState
    , class StateMachineMutexType
    >
void StateMachine<StateMachineImpl,IState,StateMachineMutexType>::pickUpRunningActiveStates()
#else
template
    < class StateMachineImpl
    , class IState
    >
void StateMachine<StateMachineImpl,IState>::pickUpRunningActiveStates()
#endif
{
    bool allRunningActiveStatesJoined = false;
    do
    {
        STTCL_STATEMACHINE_SAFESECTION_START(internalLockGuard);
            allRunningActiveStatesJoined = activeStatesRunning.empty();
        STTCL_STATEMACHINE_SAFESECTION_END;
        if(!allRunningActiveStatesJoined)
        {
            StateBaseClass* activeStateToJoin = NULL;
            STTCL_STATEMACHINE_SAFESECTION_START(internalLockGuard);
                if(!activeStatesRunning.empty())
                {
                    activeStateToJoin = *(activeStatesRunning.begin());
                }
            STTCL_STATEMACHINE_SAFESECTION_END;
            if(activeStateToJoin)
            {
                activeStateToJoin->joinDoAction(static_cast<Context*>(this));
            }
        }
    } while(!allRunningActiveStatesJoined);
}

}

#endif /* STATEMACHINE_H_ */
