/*
 * State.h
 *
 *  Created on: 30.11.2011
 *      Author: Admin
 */

#ifndef STATE_H_
#define STATE_H_

namespace sttcl
{

template<class StateMachineImpl, class IState>
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
    friend class StateMachine<StateMachineImpl,IState>;

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
     * Default implementation for the changeState() method.
     * @param context A pointer to the containing state machine.
     * @param newState The new sibling state the containing state machine should change to.
     */
    void changeStateImpl(Context* context,StateBase<StateMachineImpl,IState>* newState)
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
    void changeState(Context* context,StateBase<StateMachineImpl,IState>* newState)
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

    virtual void startDo(Context* context)
    {
        static_cast<Implementation*>(this)->startDoImpl(context);
    }

    virtual void endDo(Context* context)
    {
        static_cast<Implementation*>(this)->endDoImpl(context);
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
