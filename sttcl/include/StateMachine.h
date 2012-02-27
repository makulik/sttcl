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
 * 3) Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products
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

#include "State.h"
#include <cassert>

namespace sttcl
{

/**
 * Represents the base class for a state machine.
 *
 * @tparam StateMachineImpl Specifies the class implementing the state machine.
 * @tparam IState Specifies the internal interface of state implementations for the state
 *                machine.
 */
template<class StateMachineImpl, class IState>
class StateMachine
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

public:
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
    	if(isInitialized())
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
    	if(!isFinalizing())
    	{
			flags.finalizing = true;
			static_cast<Context*>(this)->finalizeImpl(finalizeSubStateMachines);
			flags.finalizing = false;
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
     * Indicates that the state machine is initialized.
     * @return \c true if the state machine is initialized, \c false otherwise.
     */
    bool isInitialized() const
    {
        return flags.initialized;
    }

    /**
     * Indicates that the state machine is currently initializing.
     * @return \c true if the state machine is currently initializing, \c false otherwise.
     */
    bool isInitalizing() const
    {
        return flags.initializing;
    }

    /**
     * Indicates that the state machine is finalized.
     * @return \c true if the state machine is finalized, \c false otherwise.
     */
    bool isFinalized() const
    {
        return flags.finalized;
    }

    /**
     * Indicates that the state machine is currently finalizing.
     * @return \c true if the state machine is currently finalizing, \c false otherwise.
     */
    bool isFinalizing() const
    {
        return flags.finalizing;
    }

    /**
     * Gets the current state.
     *
     * @return The current state.
     */
    inline StateBaseClass* getState() const
    {
        return state;
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
            flags.initializing = true;
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
            changeState(getInitialState());
        	StateBaseClass* currentState = getState();
        	if(currentState)
        	{
        		currentState->initSubStateMachines(force);
        	}
            flags.initializing = false;
            flags.finalized = false;
            flags.initialized = true;
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
        if(!isFinalized() && state)
        {
            if(finalizeSubStateMachines)
            {
                state->finalizeSubStateMachines(true);
            }
            exitCurrentState();
        }
        setState(0);
        flags.finalized = true;
        flags.initialized = false;
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
    void changeState(typename StateMachine<StateMachineImpl,IState>::StateBaseClass* newState);

    /**
     * Sets the state machines current state without calling any state operations.
     * @param newState
     */
    inline void setState(StateBaseClass* newState)
    {
    	state = newState;
    }

    /**
     * Gets the initial state of the state machine.
     *
     * @return The initial state of the state machine.
     */
    StateBaseClass* getInitialState() const
    {
    	StateBaseClass* result = static_cast<const Context*>(this)->getInitialStateImpl();
    	assert(result);
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

    /**
     * Default implementation for isReady().
     *
     * @return \c true if the state machine is ready to process events, \c false otherwise.
     */
    inline bool isReadyImpl() const
    {
        return flags.initialized && !isFinalized();
    }


    void exitCurrentState();
    void enterNewState();

private:
    StateBaseClass* state;
    StateMachineFlags flags;

};

template<class StateMachineImpl, class IState>
void StateMachine<StateMachineImpl,IState>::changeState(typename StateMachine<StateMachineImpl,IState>::StateBaseClass* newState)
{
    if(!isFinalized() || isInitalizing())
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

template<class StateMachineImpl, class IState>
void StateMachine<StateMachineImpl,IState>::exitCurrentState()
{
    if(state)
    {
        state->endDo(static_cast<StateMachine<StateMachineImpl,IState>::Context*>(this));
        state->exit(static_cast<StateMachine<StateMachineImpl,IState>::Context*>(this));
    }
}

template<class StateMachineImpl, class IState>
void StateMachine<StateMachineImpl,IState>::enterNewState()
{
    state->entry(static_cast<StateMachine<StateMachineImpl,IState>::Context*>(this));
    state->startDo(static_cast<StateMachine<StateMachineImpl,IState>::Context*>(this));
}

}

#endif /* STATEMACHINE_H_ */
