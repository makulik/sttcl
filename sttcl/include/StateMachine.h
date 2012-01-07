/*
 * StateMachine.h
 *
 *  Created on: 30.11.2011
 *      Author: Admin
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
    struct StateMachineFlags
    {
        unsigned char initialized:1;
        unsigned char initializing:1;
        unsigned char finalized:1;
        unsigned char finalizing:1;

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
        flags.finalizing = true;
        static_cast<Context*>(this)->finalizeImpl(finalizeSubStateMachines);
        flags.finalizing = false;
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
     * Default implementation for finalize().
     *
     * @param finalizeSubStateMachines Indicates to finalize any sub state machines.
     */
    inline void finalizeImpl(bool finalizeSubStateMachines)
    {
        if(!isFinalized() && !isFinalizing() && state)
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

    inline void subStateMachineCompletedImpl()
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
