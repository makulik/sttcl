/*
 * TestTransitionMocks.h
 *
 *  Created on: Jul 3, 2013
 *      Author: user
 */

#ifndef TESTTRANSITIONMOCKS_H_
#define TESTTRANSITIONMOCKS_H_

template
    < class ContextStateMachine
    , class EventHandlerInterface
    >
struct TransitionKey
{
    typedef void (EventHandlerInterface::*EventHandler)(ContextStateMachine* context);

    EventHandler& eventId;
    ContextStateMachine::StateBaseClass& targetState;

    TransitionKey(EventHandler& eventId_,ContextStateMachine::StateBaseClass& targetState_)
    : eventId(eventId_)
    , targetState(targetState_)
    {
    }

    TransitionKey(const TransitionKey& rhs)
    : eventId(rhs.eventId)
    , targetState(rhs.targetState)
    {
    }

    TransitionKey& operator=(const TransitionKey& rhs)
    {
        eventId = rhs.eventId;
        targetState = rhs.targetState;
        return *this;
    }

    bool operator==(const TransitionKey& rhs)
    {
        return ( (&eventId ==  &rhs.eventId) && (&targetState == &rhs.targetState));
    }

    bool operator!=(const TransitionKey& rhs)
    {
        return !TransitionKey::operator==(rhs);
    }

    bool operator<(const TransitionKey& rhs)
    {
        return ( (&eventId < &rhs.eventId) && (&targetState < &rhs.targetState));
    }
};

class GuardFunctor
{
public:

  // two possible functions to call member function. virtual cause derived
  // classes will use a pointer to an object and a pointer to a member function
  // to make the function call
  virtual bool operator()(Demo3bStateMachine* context)=0;  // call using operator
};

class ActionFunctor
{
public:

  // two possible functions to call member function. virtual cause derived
  // classes will use a pointer to an object and a pointer to a member function
  // to make the function call
  virtual void operator()(Demo3bStateMachine* context)=0;  // call using operator
};

template <class T> class TGuardFunctor
: public GuardFunctor
{
private:
      bool (T::*fpt)(Demo3bStateMachine* context);   // pointer to member function
      T* pt2Object;                  // pointer to object

public:

      // constructor - takes pointer to an object and pointer to a member and stores
      // them in two private variables
      TGuardFunctor(T* _pt2Object, bool (T::*_fpt)(Demo3bStateMachine* context))
      { pt2Object = _pt2Object;  fpt=_fpt; };

      // override operator "()"
      virtual bool operator()(Demo3bStateMachine* context)
      { (*pt2Object.*fpt)(context);};              // execute member function
};


template <class T> class TActionFunctor
: public ActionFunctor
{
private:
      void (T::*fpt)(Demo3bStateMachine* context);   // pointer to member function
      T* pt2Object;                  // pointer to object

public:

      // constructor - takes pointer to an object and pointer to a member and stores
      // them in two private variables
      TActionFunctor(T* _pt2Object, void (T::*_fpt)(Demo3bStateMachine* context))
      { pt2Object = _pt2Object;  fpt=_fpt; };

      // override operator "()"
      virtual void operator()(Demo3bStateMachine* context)
      { (*pt2Object.*fpt)(context);};              // execute member function
};

class Transition
{
public:
    typedef bool (*GuardFuncType)(Demo3bStateMachine* context);
    typedef void (*ActionFuncType)(Demo3bStateMachine* context);

    Transition(EventHandler& eventId_,StateBase& targetState_,GuardFunctor* guardFunctor)
    : key_(eventId_,targetState_)
    , guardFunctor_(guardFunctor)
    {}
//        typedef std::map<EventHandler,>


    const TransitionKey& key() const { return key_; }
    Transition(EventHandler& eventId_,StateBase& targetState_,GuardFunctor* guardFunctor)
    : key_(eventId_,targetState_)
    , guardFunctor_(guardFunctor)
    {}

private:
    TransitionKey key_;
    GuardFunctor guardFunctor_;
    ActionFunctor actionFunctor_;
};

#endif /* TESTTRANSITIONMOCKS_H_ */
