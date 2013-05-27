/**
 * @file CompositeState.h
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

namespace internal
{
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
	InnerStateType* getStateHistory() const
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
		if(currentState)
        {
            currentState->finalizeSubStateMachines(true);
        }
		return 0;
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
	InnerStateType* getStateHistory() const
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
	InnerStateType* getStateHistory() const
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
		if(lastState)
		{
			compositeState->changeState(lastState);
		}
		else
		{
			compositeState->initialize();
		}
		InnerStateType* currentState = compositeState->getState();
		if(!currentState)
        {
            compositeState->finalize(false);
        }
		else
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
	typedef sttcl::internal::CompositeStateBase<InnerStateType> RESULT_TYPE;
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
	typedef sttcl::internal::CompositeStateBaseWithDeepHistory<InnerStateType> RESULT_TYPE;
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
	typedef sttcl::internal::CompositeStateBaseWithShallowHistory<InnerStateType> RESULT_TYPE;
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
#if defined(STTCL_THREADSAFE_IMPL)
    , class StateMachineBaseImpl = StateMachine<CompositeStateImpl, IInnerState, typename StateMachineImpl::MutexType>
#else
    , class StateMachineBaseImpl = StateMachine<CompositeStateImpl, IInnerState>
#endif
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
     * Default implementation of the subStateMachineCompleted() method.
     */
    inline void subStateMachineCompletedImpl()
    {
    	// TODO: Propagate completion events asynchronously (e.g. for Region and ConcurrentCompositeState)
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
    	StateMachineBaseImpl::setState(this->resumeStateHistory(static_cast<CompositeStateImpl*>(this)));
    }

    /**
     * Called when this state is left.
     *
     * @param context The state machine context.
     */
    void exitImpl(Context* context)
    {
		StateMachineBaseImpl::exitCurrentState();
    	StateMachineBaseImpl::setState(this->finalizeStateHistory(static_cast<CompositeStateImpl*>(this)));
    	if(!StateMachineBaseImpl::getState())
    	{
    	    StateMachineBaseImpl::finalize(false);
    	}
    	StateBaseImpl::exitImpl(context);
    }

    /**
     * Default implementation for isReady().
     *
     * @return \c true if the state machine is ready to process events, \c false otherwise.
     */
    inline bool isReadyImpl() const
    {
        return (CompositeStateHistoryBaseClass::getStateHistory() ||
                StateMachineImplementationBase::isReadyImpl());
    }

protected:
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
