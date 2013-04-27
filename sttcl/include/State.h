/**
 * @file State.h
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

#ifndef STATE_H_
#define STATE_H_

#include <SttclConfig.h>

namespace sttcl
{

template
    < class StateMachineImpl
    , class IState
#if defined(STTCL_THREADSAFE_IMPL)
    , class StateMachineMutexType
#endif
    >
class StateMachine;

/**
 * Represents a particular state machines state base class.
 *
 * @tparam StateMachineImpl The state machine implementation type.
 * @tparam IState Specifies the internal interface of state implementations for the state
 *                machine.
 */
template<class StateMachineImpl,class IState>
class StateBase
: public IState
{
#if defined(STTCL_THREADSAFE_IMPL)
    friend class StateMachine<StateMachineImpl,IState,typename StateMachineImpl::MutexType>;
#else
    friend class StateMachine<StateMachineImpl,IState>;
#endif

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
     * Called by the containing StateMachine to finalize any sub state machines.
     * @param recursive If \c true further sub state machines should be finalized
     *                  recursively.
     */
    virtual void finalizeSubStateMachines(bool recursive) = 0;

    /**
     * Called by the containing StateMachine to initialize any sub state machines.
     * @param recursive If \c true further sub state machines should be initialized
     *                  recursively.
     */
    virtual void initSubStateMachines(bool recursive) = 0;

    /**
     * Called by the containing state machine when the state is entered.
     * @param context A pointer to the containing state machine.
     */
    virtual void entry(Context* context) = 0;
    /**
     * Called by the containing state machine when the state is left.
     * @param context A pointer to the containing state machine.
     */
    virtual void exit(Context* context) = 0;
    /**
     * Called by the containing state machine after the state was entered.
     * @param context A pointer to the containing state machine.
     */
    virtual void startDo(Context* context) = 0;
    /**
     * Called by the containing state machine before the state is left.
     * @param context A pointer to the containing state machine.
     */
    virtual void endDo(Context* context) = 0;

    /**
     * Called by the containig state machine to pickup finished asynchronous doAction threads.
     * @param context A pointer to the containing state machine.
     */
    virtual void joinDoAction(Context* context) = 0;

    /**
     * Default implementation for the changeState() method.
     * @param context A pointer to the containing state machine.
     * @param newState The new sibling state the containing state machine should change to.
     */
    void changeStateImpl(Context* context,StateBase<StateMachineImpl,IState>* newState)
    {
		context->changeState(newState);
    }

    /**
     * Default implementation for the changeState() method.
     * @param context A pointer to the containing state machine.
     * @param newState The new sibling state the containing state machine should change to.
     */
    template<class StateMachineContext>
    void changeStateImpl(StateMachineContext* context,StateBase<StateMachineImpl,IState>* newState)
    {
    	context->changeState(newState);
    }
protected:

    /**
     * Constructor for class StateBase.
     */
    StateBase() {}
    /**
     * Destructor for class StateBase.
     */
    virtual ~StateBase() {}

};

/**
 * Represents a particular state machines state implementation base class.
 *
 * @tparam StateImpl The state implementation type.
 * @tparam StateMachine The state machine implementation type.
 * @tparam IState Specifies the internal interface of state implementations for the state
 *                machine.
 */
template<class StateImpl,class StateMachineImpl,class IState>
class State
: public StateBase<StateMachineImpl,IState>
{
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
     * The first parameter is a pointer to the containing state machine, the second parameter
     * indicates that the state do action is called the first time when \c true.
     */
    typedef void (Implementation::*StateDoAction)(Context*,bool);

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
     * Default implementation for the startDo() method.
     * @param context A pointer to the containing state machine.
     */
    inline void startDoImpl(Context* context)
    {
        if(doAction)
        {
            (static_cast<Implementation*>(this)->*doAction)(context,true);
        }
    }

    /**
     * Default implementation for the endDo() method.
     * @param context A pointer to the containing state machine.
     */
    inline void endDoImpl(Context* context)
    {
    }

    /**
     * Default implementation for the joinDoAction() method.
     * @param context A pointer to the containing state machine.
     */
    inline void joinDoActionImpl(Context* context)
    {
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
     * Constructor for class State.
     *
     * @param argDoAction A pointer to the state do action.
     */
    State(StateDoAction argDoAction = 0)
    : doAction(argDoAction)
    {
    }

    /**
     * Destructor for class State.
     */
    virtual ~State()
    {
    }

    /**
     * Changes \em context state machine to another sibling state.
     * @param context A pointer to the containing state machine.
     * @param newState A pointer to the sibling state to change to.
     */
    void changeState(Context* context,StateBaseType* newState)
    {
    	static_cast<Implementation*>(this)->changeStateImpl(context,newState);
    }

    /**
     * Changes \em context state machine to another sibling state.
     * @param context A pointer to the containing state machine.
     * @param newState A pointer to the sibling state to change to.
     */
    template<class StateMachineContext>
    void changeState(StateMachineContext* context,StateBaseType* newState)
    {
    	static_cast<Implementation*>(this)->changeStateImpl(context,newState);
    }

    /**
     * The state do action.
     */
    StateDoAction doAction;

private:
    virtual void entry(Context* context)
    {
        static_cast<Implementation*>(this)->entryImpl(context);
    }

    virtual void exit(Context* context)
    {
        static_cast<Implementation*>(this)->exitImpl(context);
    }

//    template<class StateMachineContext>
//    virtual void entry(StateMachineContext* context)
//    {
//        static_cast<Implementation*>(this)->entryImpl(context);
//    }
//
//    template<class StateMachineContext>
//    virtual void exit(StateMachineContext* context)
//    {
//        static_cast<Implementation*>(this)->exitImpl(context);
//    }

    virtual void startDo(Context* context)
    {
    	// Run the do action
        static_cast<Implementation*>(this)->startDoImpl(context);

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
			}
		}
    }

    virtual void endDo(Context* context)
    {
        static_cast<Implementation*>(this)->endDoImpl(context);
    }

    virtual void joinDoAction(Context* context)
    {
        static_cast<Implementation*>(this)->joinDoActionImpl(context);
    }

    virtual void finalizeSubStateMachines(bool recursive)
    {
        static_cast<Implementation*>(this)->finalizeSubStateMachinesImpl(recursive);
    }

    virtual void initSubStateMachines(bool recursive)
    {
        static_cast<Implementation*>(this)->initSubStateMachinesImpl(recursive);
    }

};
}

#endif /* STATE_H_ */
