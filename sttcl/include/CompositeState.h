/*
 * CompositeState.h
 *
 *  Created on: 20.12.2011
 *      Author: Admin
 */

#ifndef COMPOSITESTATE_H_
#define COMPOSITESTATE_H_

#include "State.h"

namespace sttcl
{

/**
 * Represents a composite states history pseudo state behavior.
 */
struct CompositeStateHistoryType
{
	enum Values
	{
		/**
		 * Default behavior of the history pseudo state. No history is tracked.
		 */
		None ,
		/**
		 * Deep history pseudo state behavior. Nested history pseudo states will be resumed
		 * on (re-)entering the composite state.
		 */
		Deep ,
		/**
		 * Shallow history pseudo state behavior. Nested history pseudo states will be ignored
		 * on (re-)entering the composite state.
		 */
		Shallow ,
	};
};

/**
 * Represents the default base class for a composite state.
 * @tparam InnerStateType The state base class type of the composite states inner states.
 */
template<class InnerStateType>
class CompositeStateBase
{
protected:
    /**
     * Constructor for class CompositeStateBase.
     */
	CompositeStateBase()
	{
	}
    /**
     * Destructor for class CompositeStateBase.
     */
	~CompositeStateBase()
	{
	}

	/**
	 * Saves the current inner state of the composite state.
	 * @param currentState
	 */
	void saveCurrentState(InnerStateType* currentState)
	{
	}

	/**
	 * Gets the last saved state.
	 * @return
	 */
	InnerStateType* getStateHistory()
	{
		return 0;
	}

	/**
	 * Resumes the state history.
	 * @tparam CompositeStateImpl The composite state implementation class.
	 * @param compositeState A pointer to the composite state implementation.
	 * @return The current inner state of the composite state.
	 */
	template<class CompositeStateImpl>
	InnerStateType* resumeStateHistory(CompositeStateImpl* compositeState)
	{
		if(!compositeState->isReady())
		{
			compositeState->initialize();
		}
		InnerStateType* currentState = compositeState->getState();
		return currentState;
	}

	/**
	 * Resets the state history.
	 * @tparam CompositeStateImpl The composite state implementation class.
	 * @param compositeState A pointer to the composite state implementation.
	 * @return The current inner state of the composite state.
	 */
	template<class CompositeStateImpl>
	InnerStateType* finalizeStateHistory(CompositeStateImpl* compositeState)
	{
		InnerStateType* currentState = compositeState->getState();
		return currentState;
	}

};

/**
 * Represents the base class for a composite state with a deep history pseudo state.
 * @tparam InnerStateType The state base class type of the composite states inner states.
 */
template<class InnerStateType>
class CompositeStateBaseWithDeepHistory
{
protected:
    /**
     * Constructor for class CompositeStateBaseWithDeepHistory.
     */
	CompositeStateBaseWithDeepHistory()
	: lastState(0)
	{
	}
    /**
     * Destructor for class CompositeStateBaseWithDeepHistory.
     */
	~CompositeStateBaseWithDeepHistory()
	{
	}

	/**
	 * Saves the current inner state of the composite state.
	 * @param currentState
	 */
	void saveCurrentState(InnerStateType* currentState)
	{
		lastState = currentState;
	}

	/**
	 * Gets the last saved state.
	 * @return
	 */
	InnerStateType* getStateHistory()
	{
		return lastState;
	}

	/**
	 * Resumes the state history.
	 * @tparam CompositeStateImpl The composite state implementation class.
	 * @param compositeState A pointer to the composite state implementation.
	 * @return The current inner state of the composite state.
	 */
	template<class CompositeStateImpl>
	InnerStateType* resumeStateHistory(CompositeStateImpl* compositeState)
	{
		if(lastState != 0)
		{
			compositeState->changeState(lastState);

		}
		else
		{
			compositeState->initialize();
		}
		InnerStateType* currentState = compositeState->getState();
		if(currentState)
		{
			currentState->initSubStateMachines(true);
		}
		return currentState;
	}

	/**
	 * Resets the state history.
	 * @tparam CompositeStateImpl The composite state implementation class.
	 * @param compositeState A pointer to the composite state implementation.
	 * @return The current inner state of the composite state.
	 */
	template<class CompositeStateImpl>
	InnerStateType* finalizeStateHistory(CompositeStateImpl* compositeState)
	{
		InnerStateType* currentState = compositeState->getState();
		if(currentState)
		{
			currentState->finalizeSubStateMachines(true);
		}
		saveCurrentState(currentState);
		return 0;
	}

	InnerStateType* lastState;
};

/**
 * Represents the base class for a composite state with a shallow history pseudo state.
 * @tparam InnerStateType The state base class type of the composite states inner states.
 */
template<class InnerStateType>
class CompositeStateBaseWithShallowHistory
{
protected:
    /**
     * Constructor for class CompositeStateBaseWithShallowHistory.
     */
	CompositeStateBaseWithShallowHistory()
	: lastState(0)
	{
	}
    /**
     * Destructor for class CompositeStateBaseWithShallowHistory.
     */
	~CompositeStateBaseWithShallowHistory()
	{
	}

	/**
	 * Saves the current inner state of the composite state.
	 * @param currentState
	 */
	void saveCurrentState(InnerStateType* currentState)
	{
		lastState = currentState;
	}

	/**
	 * Gets the last saved state.
	 * @return
	 */
	InnerStateType* getStateHistory()
	{
		return lastState;
	}

	/**
	 * Resumes the state history.
	 * @tparam CompositeStateImpl The composite state implementation class.
	 * @param compositeState A pointer to the composite state implementation.
	 * @return The current inner state of the composite state.
	 */
	template<class CompositeStateImpl>
	InnerStateType* resumeStateHistory(CompositeStateImpl* compositeState)
	{
		if(lastState != 0)
		{
			compositeState->changeState(lastState);
		}
		else
		{
			compositeState->initialize();
		}
		InnerStateType* currentState = compositeState->getState();
		if(currentState)
		{
			currentState->initSubStateMachines(false);
		}
		return currentState;
	}

	/**
	 * Resets the state history.
	 * @tparam CompositeStateImpl The composite state implementation class.
	 * @param compositeState A pointer to the composite state implementation.
	 * @return The current inner state of the composite state.
	 */
	template<class CompositeStateImpl>
	InnerStateType* finalizeStateHistory(CompositeStateImpl* compositeState)
	{
		InnerStateType* currentState = compositeState->getState();
		if(currentState)
		{
			currentState->finalizeSubStateMachines(false);
		}
		saveCurrentState(currentState);
		return 0;
	}

	InnerStateType* lastState;
};

namespace internal
{
/**
 * Used to select a pseudo state history behavior base class for class CompositeState.
 * @tparam HistoryType The history pseudo state type.
 * @tparam InnerStateType The state base class type of the composite states inner states.
 */
template<CompositeStateHistoryType::Values HistoryType, class InnerStateType>
struct CompositeStateBaseSelector
{
	/**
	 * The composite state base class implementing the history pseudo state behavior.
	 */
	typedef CompositeStateBase<InnerStateType> RESULT_TYPE;
};

/**
 * Specializes CompositeStateBaseSelector for deep history pseudo state behavior.
 */
template<class InnerStateType>
struct CompositeStateBaseSelector<CompositeStateHistoryType::Deep,InnerStateType>
{
	/**
	 * The composite state base class implementing the history pseudo state behavior.
	 */
	typedef CompositeStateBaseWithDeepHistory<InnerStateType> RESULT_TYPE;
};

/**
 * Specializes CompositeStateBaseSelector for shallow history pseudo state behavior.
 */
template<class InnerStateType>
struct CompositeStateBaseSelector<CompositeStateHistoryType::Shallow,InnerStateType>
{
	/**
	 * The composite state base class implementing the history pseudo state behavior.
	 */
	typedef CompositeStateBaseWithShallowHistory<InnerStateType> RESULT_TYPE;
};
}

/**
 * Represents the base class for a composite state implementation.
 * @tparam CompositeStateImpl The implementing class.
 * @tparam StateMachineImpl The implementing class.
 * @tparam IInnerState The inner state's interface class type.
 * @tparam HistoryType The composite states history pseudo state type.
 * @tparam StateBaseImpl The composite states base state implementation type.
 * @tparam StateMachineBaseImpl The composite states base state machine implementation type.
 */
template
< class CompositeStateImpl
, class StateMachineImpl
, class IInnerState
, CompositeStateHistoryType::Values HistoryType = CompositeStateHistoryType::None
, class StateBaseImpl = State<CompositeStateImpl,StateMachineImpl,typename StateMachineImpl::StateInterface>
, class StateMachineBaseImpl = StateMachine<CompositeStateImpl, IInnerState>
>
class CompositeState
: public StateBaseImpl
, public StateMachineBaseImpl
, public internal::CompositeStateBaseSelector<HistoryType,typename StateMachineBaseImpl::StateBaseClass>::RESULT_TYPE
{
public:
    /**
     * The implementation class type.
     */
    typedef CompositeStateImpl Implementation;

    /**
     * The state machine implementation type.
     */
    typedef StateMachineImpl Context;

    /**
     * The composite states base state implementation type class.
     */
    typedef StateBaseImpl StateImplementationBase;

    /**
     * The composite states base state machine implementation type class.
     */
    typedef StateMachineBaseImpl StateMachineImplementationBase;

    /**
     * The state do action type.
     */
    typedef void (Implementation::*StateDoAction)(Context*,bool);

    /**
     * The composite state base class regarding state history policy.
     */
	typedef typename internal::CompositeStateBaseSelector<HistoryType,typename StateMachineBaseImpl::StateBaseClass>::RESULT_TYPE CompositeStateHistoryBaseClass;

	/**
	 * The inner state class.
	 */
	typedef typename StateMachineBaseImpl::StateBaseClass InnerStateClass;

	/**
	 * The outer state interface.
	 */
	typedef typename StateMachineImpl::StateInterface OuterStateInterface;

	/**
	 * The state interface.
	 */
	typedef typename StateMachineBaseImpl::StateInterface StateInterface;

	/**
	 * Constructor for class CompositeState.
	 * @param argDoAction The composite state do action.
	 */
	CompositeState(StateDoAction argDoAction = 0)
	: StateBaseImpl(argDoAction)
	{
	}

	/**
	 * Destructor for class CompositeState.
	 */
	virtual ~CompositeState()
	{
	}

    /**
     * Changes the composite state machine to \em newState.
     * @param newState The inner state to change to.
     */
    void changeState(InnerStateClass* newState)
    {
    	StateMachineBaseImpl::changeState(newState);
    }

    /**
     * Changes \em context state machine to another sibling state.
     * @param context A pointer to the containing state machine.
     * @param newState A pointer to the sibling state to change to.
     */
    void changeState(Context* context,StateBase<StateMachineImpl,OuterStateInterface>* newState)
    {
    	StateBaseImpl::changeState(context,newState);
    }

    /**
     * Default implementation for the initialize() method.
     * @param force Indicates to finalize the state machine before (re-)initializing.
     * @return The ready state of the state machine.
     */
    bool initializeImpl(bool force)
    {
    	return static_cast<StateMachineBaseImpl*>(this)->initializeImpl(force);
    }

    /**
     * Default implementation for the finalize() method.
     *
     * @param finalizeSubStateMachines Indicates to finalize any sub state machines.
     */
    inline void finalizeImpl(bool finalizeSubStateMachines)
    {
    	static_cast<StateMachineBaseImpl*>(this)->finalizeImpl(finalizeSubStateMachines);
    	subStateMachineCompleted();
    }

    /**
     * Default implementatin of the subStateMachineCompleted() method.
     */
    inline void subStateMachineCompletedImpl()
    {
    }

    /**
     * Notifies the implementation class when the sub state machine has finished.
     */
    inline void subStateMachineCompleted()
    {
    	static_cast<CompositeStateImpl*>(this)->subStateMachineCompletedImpl();
    }

    /**
     * Called when this state is entered.
     *
     * @param context The state machine context.
     */
    void entryImpl(Context* context)
    {
    	StateBaseImpl::entryImpl(context);
    	StateMachineBaseImpl::setState(resumeStateHistory(static_cast<CompositeStateImpl*>(this)));
    }

    /**
     * Called when this state is left.
     *
     * @param context The state machine context.
     */
    void exitImpl(Context* context)
    {
		StateMachineBaseImpl::exitCurrentState();
    	StateMachineBaseImpl::setState(finalizeStateHistory(static_cast<CompositeStateImpl*>(this)));
    	StateBaseImpl::exitImpl(context);
    }

protected:

    /**
     * Called by the containing StateMachine to finalize any sub state machines.
     * @param recursive If \c true further sub state machines should be finalized
     *                  recursively.
     */
    virtual void finalizeSubStateMachines(bool recursive)
    {
    	if(!recursive)
    	{
    		static_cast<StateMachineBaseImpl*>(this)->finalize(recursive);
    	}
    }

    /**
     * Called by the containing StateMachine to initialize any sub state machines.
     * @param recursive If \c true further sub state machines should be initialized
     *                  recursively.
     */
    virtual void initSubStateMachines(bool recursive)
    {
		InnerStateClass* currentState = StateMachineBaseImpl::getState();
    	if(!recursive)
    	{
    		if(currentState != static_cast<CompositeStateImpl*>(this)->getInitialState())
    		{
    			StateMachineBaseImpl::initialize(true);
    		}
    	}
    	else if(StateMachineBaseImpl::isReady())
    	{
    		if(currentState)
    		{
    			currentState->initSubStateMachines(recursive);
    		}
    	}
    	else
    	{
			StateMachineBaseImpl::initialize(true);
    	}
    }
};

}

#endif /* COMPOSITESTATE_H_ */
