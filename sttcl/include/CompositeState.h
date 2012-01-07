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

struct CompositeStateHistoryType
{
	enum Values
	{
		None ,
		Deep ,
		Shallow ,
	};
};

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
	 * @param compositeState
	 * @return
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

	template<class CompositeStateImpl>
	InnerStateType* finalizeStateHistory(CompositeStateImpl* compositeState)
	{
		InnerStateType* currentState = compositeState->getState();
		return currentState;
	}

};

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
	 * @param compositeState
	 * @return
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
	 * @param compositeState
	 * @return
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

template<CompositeStateHistoryType::Values, class InnerStateType>
struct CompositeStateBaseSelector
{
	typedef CompositeStateBase<InnerStateType> RESULT_TYPE;
};

template<class InnerStateType>
struct CompositeStateBaseSelector<CompositeStateHistoryType::Deep,InnerStateType>
{
	typedef CompositeStateBaseWithDeepHistory<InnerStateType> RESULT_TYPE;
};

template<class InnerStateType>
struct CompositeStateBaseSelector<CompositeStateHistoryType::Shallow,InnerStateType>
{
	typedef CompositeStateBaseWithShallowHistory<InnerStateType> RESULT_TYPE;
};

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
, public CompositeStateBaseSelector<HistoryType,typename StateMachineBaseImpl::StateBaseClass>::RESULT_TYPE
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

    typedef StateBaseImpl StateImplementationBase;

    typedef StateMachineBaseImpl StateMachineImplementationBase;

    /**
     * The state do action type.
     */
    typedef void (Implementation::*StateDoAction)(Context*,bool);

    /**
     * The composite state base class regarding state history policy.
     */
	typedef typename CompositeStateBaseSelector<HistoryType,typename StateMachineBaseImpl::StateBaseClass>::RESULT_TYPE CompositeStateHistoryBaseClass;

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
	 * @param argDoAction
	 */
	CompositeState(StateDoAction argDoAction = 0)
	: StateBaseImpl(argDoAction)
	{
	}

	/**
	 * Destructor for class CompositeState.
	 */
	~CompositeState()
	{
	}

    /**
     * Changes \em context state machine to another sibling state.
     * @param context
     * @param newState
     */
    void changeState(InnerStateClass* newState)
    {
    	StateMachineBaseImpl::changeState(newState);
    }

    /**
     * Changes \em context state machine to another sibling state.
     * @param context
     * @param newState
     */
    void changeState(Context* context,StateBase<StateMachineImpl,OuterStateInterface>* newState)
    {
    	StateBaseImpl::changeState(context,newState);
    }

    bool initializeImpl(bool force)
    {
    	return static_cast<StateMachineBaseImpl*>(this)->initializeImpl(force);
    }

    /**
     * Default implementation for finalize().
     *
     * @param finalizeSubStateMachines Indicates to finalize any sub state machines.
     */
    inline void finalizeImpl(bool finalizeSubStateMachines)
    {
    	static_cast<StateMachineBaseImpl*>(this)->finalizeImpl(finalizeSubStateMachines);
    	subStateMachineCompleted();
    }

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

    virtual void finalizeSubStateMachines(bool recursive)
    {
    	if(!recursive)
    	{
    		static_cast<StateMachineBaseImpl*>(this)->finalize(recursive);
    	}
    }

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
