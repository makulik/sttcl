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
 * @tparam StateMachine The state machine implementation type.
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

    virtual void finalizeSubStateMachines(bool recursive) = 0;
    virtual void initSubStateMachines(bool recursive) = 0;
    virtual void entry(Context* context) = 0;
    virtual void exit(Context* context) = 0;
    virtual void startDo(Context* context) = 0;
    virtual void endDo(Context* context) = 0;

protected:

    /**
     * Constructor for class StateBase.
     */
    StateBase() {}
    /**
     * Destructor for class StateBase.
     */
    virtual ~StateBase() {}

    /**
     * Default enter() implementation.
     *
     * @param context The state machine context.
     */
    inline void entryImpl(Context* context)
    {
    }

    /**
     * Default exit() implementation.
     *
     * @param context The state machine context.
     */
    inline void exitImpl(Context* context)
    {
    }

    /**
     * Default startDo() implementation.
     *
     * @param context The state machine context.
     */
    inline void startDoImpl(Context* context)
    {
    }

    /**
     * Default endDo() implementation.
     *
     * @param context The state machine context.
     */
    inline void endDoImpl(Context* context)
    {
    }

    void changeStateImpl(Context* context,StateBase<StateMachineImpl,IState>* newState)
    {
    	context->changeState(newState);
    }
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
     * The state do action type.
     */
    typedef void (Implementation::*StateDoAction)(Context*,bool);

    virtual void finalizeSubStateMachines(bool recursive)
    {
    }

    virtual void initSubStateMachines(bool recursive)
    {
    }

    inline void startDoImpl(Context* context)
    {
        if(doAction)
        {
            (static_cast<Implementation*>(this)->*doAction)(context,true);
        }
    }

    inline void endDoImpl(Context* context)
    {
    }

protected:
    /**
     * Constructor for class State.
     *
     * @param impl A pointer to the state implementation.
     */
    State(StateDoAction argDoAction = 0)
    : doAction(argDoAction)
    {
    }

    /**
     * Changes \em context state machine to another sibling state.
     * @param context
     * @param newState
     */
    void changeState(Context* context,StateBase<StateMachineImpl,IState>* newState)
    {
    	changeStateImpl(context,newState);
    }

    StateDoAction doAction;

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

};
}

#endif /* STATE_H_ */
