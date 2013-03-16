/**
 * @file Region.h
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

#ifndef REGION_H_
#define REGION_H_

#include "CompositeState.h"
#include "ActiveState.h"
#include "RefCountPtr.h"
#include "SttclMutex.h"
#include "SttclSemaphore.h"
#include "EventQueue.h"

namespace sttcl
{

template
< class RegionContainerImpl
, class IInnerState
, class EventArgs
>
class RegionBase;

namespace internal
{
/**
 * Used to select an EventArgs passing interface for ConcurrentCompositeState and Region.
 * @tparam EventArgsType The event arguments type.
 * @tparam InnerStateType The state base class type of the composite states inner states.
 */
template
< class RegionContainerImpl
, class IInnerState
, class EventArgsType
>
struct EventArgsInterfaceSelector
{
	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef sttcl::RefCountPtr<EventArgsType> RefCountPtr;

    /**
	 * The inner states event handler signature. All methods of the \em IInnerState interface
	 * must have this signature. The first parameter is a pointer to the containing state
	 * machine. The second parameter is a pointer to the region base class that contains the
	 * inner state. The third parameter is a pointer to additional event arguments as specified
	 * with the EventArgs template parameter.
	 */
    typedef void (IInnerState::*InnerEventHandler)(RegionContainerImpl*,RegionBase<RegionContainerImpl,IInnerState,EventArgsType>*,RefCountPtr);
};

/**
 * Specializes EventArgsInterfaceSelector for void (i.e. no) event arguments.
 */
template
< class RegionContainerImpl
, class IInnerState
>
struct EventArgsInterfaceSelector<RegionContainerImpl,IInnerState,void>
{
	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef sttcl::RefCountPtr<void> RefCountPtr;

    /**
	 * The inner states event handler signature. All methods of the IInnerState interface
	 * must have this signature. The first parameter is a pointer to the containing state
	 * machine. The second parameter is a pointer to additional event arguments as specified
	 * with the EventArgs template parameter.
	 */
    typedef void (IInnerState::*InnerEventHandler)(RegionContainerImpl*,RegionBase<RegionContainerImpl,IInnerState,void>*);
};

template
< class RegionContainerImpl
, class IInnerState
, class EventArgs
> class IRegionEventDispatchWithArgs
{
public:
	typedef EventArgsInterfaceSelector<RegionContainerImpl,IInnerState,EventArgs> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::RefCountPtr RefCountPtr;

	/**
     * The inner event handler signature.
     */
	typedef typename EventArgsSelectorType::InnerEventHandler InnerEventHandler;

	/**
     * Called to handle an event broadcasted from the containing ConcurrentCompositeState instance.
     * @param context A pointer to the containing state machine.
     * @param eventHandler The event handler to call inside the region thread.
     * @param eventArgs The event arguments to pass to the event handler call.
     */
	virtual void handleBroadcastedEvent(RegionContainerImpl* context,InnerEventHandler eventHandler, RefCountPtr eventArgs) = 0;

	virtual ~IRegionEventDispatchWithArgs() {}
};

template
< class RegionContainerImpl
, class IInnerState
, class EventArgs
> class IRegionEventDispatchWithoutArgs
{
public:
	typedef EventArgsInterfaceSelector<RegionContainerImpl,IInnerState,EventArgs> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::RefCountPtr RefCountPtr;

	/**
     * The inner event handler signature.
     */
	typedef typename EventArgsSelectorType::InnerEventHandler InnerEventHandler;

	/**
     * Called to handle an event broadcasted from the containing ConcurrentCompositeState instance.
     * @param context A pointer to the containing state machine.
     * @param eventHandler The event handler to call inside the region thread.
     */
	virtual void handleBroadcastedEvent(RegionContainerImpl* context,InnerEventHandler eventHandler) = 0;

	virtual ~IRegionEventDispatchWithoutArgs() {}
};

/**
 * Used to select the region event dispatch interface.
 * @tparam RegionContainerImpl
 * @tparam StateInterface
 * @tparam EventArgs
 */
template
< class RegionContainerImpl
, class IInnerState
, class EventArgs
>
struct RegionEventDispatchInterfaceSelector
{
	/**
	 * The region base event dispatch interface type.
	 */
	typedef IRegionEventDispatchWithArgs<RegionContainerImpl,IInnerState,EventArgs> RESULT_TYPE;

};

/**
 * Specializes RegionEventDispatchInterfaceSelector for void (i.e. no) event arguments.
 */
template
< class RegionContainerImpl
, class IInnerState
>
struct RegionEventDispatchInterfaceSelector<RegionContainerImpl,IInnerState,void>
{
	/**
	 * The region base event dispatch interface type.
	 */
	typedef IRegionEventDispatchWithoutArgs<RegionContainerImpl,IInnerState,void> RESULT_TYPE;

};

template
< class RegionContainerImpl
, class IInnerState
, class EventArgs
>
struct DispatchedEvent;

template
< class RegionContainerImpl
, class IInnerState
, class EventArgs
>
class RegionContainer;

}

/**
 * Represents the abstract Region base class.
 * @tparam RegionContainerImpl
 * @tparam StateInterface
 * @tparam EventArgs
 */
template
< class RegionContainerImpl
, class IInnerState
, class EventArgs = void
>
class RegionBase
: public sttcl::internal::RegionEventDispatchInterfaceSelector<RegionContainerImpl,IInnerState,EventArgs>::RESULT_TYPE
{
public:

	typedef typename sttcl::internal::RegionEventDispatchInterfaceSelector<RegionContainerImpl,IInnerState,EventArgs>::RESULT_TYPE RegionEventDispatchInterface;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename RegionEventDispatchInterface::RefCountPtr RefCountPtr;

	/**
	 * The inner states event handler signature. All methods of the IInnerState interface
	 * must have this signature. The first parameter is a pointer to the containing state
	 * machine. The second parameter is a pointer to additional event arguments as specified
	 * with the EventArgs template parameter.
	 */
    typedef typename RegionEventDispatchInterface::InnerEventHandler InnerEventHandler;

	/**
	 * Constructor for class RegionBase.
	 */
	RegionBase(RegionContainerImpl* argRegionContainer)
    : regionContainer(argRegionContainer)
	{
	}

	/**
	 * Destructor for class RegionBase.
	 */
	virtual ~RegionBase()
	{
	}

	/**
	 * Called when the region is entered.
     * @param context A pointer to the containing state machine.
	 */
	virtual void enterRegion(RegionContainerImpl* context) = 0;
	/**
	 * Called when the region is left.
     * @param context A pointer to the containing state machine.
	 */
	virtual void exitRegion(RegionContainerImpl* context) = 0;
	/**
	 * Called to finalize the region.
	 * @param recursive Indicates to finalize nested sub state machines recursively.
	 */
	virtual void finalizeRegion(bool recursive) = 0;
	/**
	 * Called to initialize the region.
	 * @param recursive Indicates to initialize nested sub state machines recursively.
	 * @return \c true when the region was successfully initialized, \c false otherwise.
	 */
	virtual bool initializeRegion(bool recursive) = 0;
	/**
	 * Called to start the region thread.
     * @param context A pointer to the containing state machine.
	 */
	virtual void startDoRegion(RegionContainerImpl* context) = 0;
	/**
	 * Called to stop the region thread.
     * @param context A pointer to the containing state machine.
	 */
	virtual void endDoRegion(RegionContainerImpl* context) = 0;
	/**
	 * Indicates that the region is initialized.
	 * @return \c true if the region is initialized, \c false otherwise.
	 */
	virtual bool isRegionInitialized() = 0;
	/**
	 * Indicates that the region is finalized.
	 * @return \c true if the region is finalized, \c false otherwise.
	 */
	virtual bool isRegionFinalized() = 0;
	/**
	 * Indicates that the region thread is currently running.
	 * @return \c true if the region thread is running, \c false otherwise.
	 */
	virtual bool isRegionThreadRunning() const = 0;
	/**
	 * Called to join the region thread after stopping it.
	 */
	virtual void joinRegionThread() = 0;

	/**
	 * Gets the actual Region implementation context.
	 * @return A pointer to the actual Region implementation.
	 */
	template<class RegionImpl>
	RegionImpl* getRegionContext()
	{
		return static_cast<RegionImpl*>(this);
	}

	/**
	 * Used to call the Region::initialize() method, when initialize() should run inside the region thread.
	 * @param recursive
	 */
	virtual void internalInitialize(bool recursive) = 0;

	virtual void internalFinalize(bool recursive) = 0;

	virtual void queueDispatchedEvent(const sttcl::internal::DispatchedEvent<RegionContainerImpl,IInnerState,EventArgs>& dispatchedEvent) = 0;

protected:
	RegionContainerImpl* regionContainer;
};

namespace internal
{

/**
 * Container struct to dispatch events to the inner region thread.
 */
template
< class RegionContainerImpl
, class IInnerState
, class EventArgs
>
struct DispatchedEvent
{
    /**
     * The RegionBase class type.
     */
    typedef RegionBase<RegionContainerImpl,IInnerState,EventArgs> RegionBaseClass;


	typedef EventArgsInterfaceSelector<RegionContainerImpl,IInnerState,EventArgs> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::RefCountPtr RefCountPtr;

	/**
     * The inner event handler signature.
     */
	typedef typename EventArgsSelectorType::InnerEventHandler InnerEventHandler;

    /**
     * The internal event handler signature.
     */
    typedef void (RegionBaseClass::*InternalEventHandler)(bool);

    /**
     * The context state machine where the event was issued.
     */
    RegionContainerImpl* context;
    /**
     * The inner region state for calling the dispatched event handler.
     */
    IInnerState* state;
    /**
     * The dispatched inner event handler method.
     */
	InnerEventHandler handler;
	/**
	 * The event arguments pointer to pass to the dispatched inner event handler method.
	 */
	mutable RefCountPtr eventArgs;
	/**
	 * The dispatched internal event handler method.
	 */
	InternalEventHandler internalHandler;
	/**
	 * The flag passed to the dispatched internal event handler method.
	 */
	bool recursiveInternalEvent;

	/**
	 * Constructor for struct DispatchedEvent, constructs an inner state event.
	 * @param argContext
	 * @param argState
	 * @param argHandler
	 * @param argEventArgs
	 */
	DispatchedEvent(RegionContainerImpl* argContext, IInnerState* argState, InnerEventHandler argHandler, RefCountPtr argEventArgs)
	: context(argContext)
	, state(argState)
	, handler(argHandler)
	, eventArgs(argEventArgs)
	, internalHandler(0)
	, recursiveInternalEvent(false)
	{
	}

	/**
	 * Constructor for struct DispatchedEvent, constructs an internal event.
	 * @param argInternalHandler
	 * @param argRecursiveInternalEvent
	 */
	DispatchedEvent(InternalEventHandler argInternalHandler, bool argRecursiveInternalEvent)
	: context(0)
	, state(0)
	, handler(0)
	, eventArgs()
	, internalHandler(argInternalHandler)
	, recursiveInternalEvent(argRecursiveInternalEvent)
	{
	}

	/**
	 * Copy constructor for struct DispatchedEvent.
	 * @param rhs
	 */
	DispatchedEvent(const DispatchedEvent& rhs)
	: context(rhs.context)
	, state(rhs.state)
	, handler(rhs.handler)
	, eventArgs(rhs.eventArgs)
	, internalHandler(rhs.internalHandler)
	, recursiveInternalEvent(rhs.recursiveInternalEvent)
	{
	}

	/**
	 * Copy constructor for struct DispatchedEvent.
	 * @param rhs
	 */
	DispatchedEvent& operator=(const DispatchedEvent& rhs)
	{
		context = rhs.context;
		state = rhs.state;
		handler = rhs.handler;
		eventArgs = rhs.eventArgs;
		internalHandler = rhs.internalHandler;
		recursiveInternalEvent = rhs.recursiveInternalEvent;
		return *this;
	}

private:
	DispatchedEvent(); // Forbidden
};

/**
 * Represents the implementation for the RegionBase class with dispatched event arguments.
 * @tparam RegionImpl The inheriting class.
 * @tparam RegionContainerImpl
 * @tparam StateInterface
 * @tparam EventArgs
 */
template
< class RegionImpl
, class RegionContainerImpl
, class IInnerState
, class EventArgs
>
class RegionBaseImplWithEventArgs
: public RegionBase<RegionContainerImpl,IInnerState,EventArgs>
{
public:
    /**
     * The implementation class type.
     */
    typedef RegionImpl Implementation;

    /**
     * The RegionBase class type.
     */
    typedef RegionBase<RegionContainerImpl,IInnerState,EventArgs> RegionBaseClass;

    typedef typename RegionBaseClass::RefCountPtr RefCountPtr;

    typedef typename RegionBaseClass::InnerEventHandler InnerEventHandler;

    RegionBaseImplWithEventArgs(RegionContainerImpl* argRegionContainer)
    : RegionBaseClass(argRegionContainer)
    {}

    virtual ~RegionBaseImplWithEventArgs() {}

    virtual void handleBroadcastedEvent(RegionContainerImpl* context,InnerEventHandler eventHandler, RefCountPtr eventArgs)
	{
		(static_cast<Implementation*>(this)->*eventHandler)(context,this,eventArgs);
	}

	/**
	 * Dispatches an event to a state inside the region. The state event handler will be executed
	 * within the context of the internal region thread.
	 * @param context
	 * @param state
	 * @param eventHandler
	 * @param eventArgs
	 */
	void dispatchEvent(RegionContainerImpl* context,IInnerState* state, InnerEventHandler eventHandler, RefCountPtr eventArgs)
	{
		if(state)
		{
			queueDispatchedEvent(sttcl::internal::DispatchedEvent<RegionContainerImpl,IInnerState,EventArgs>(context,state,eventHandler,eventArgs));
		}
	}

protected:
	void callDispatchedEventHandler(RegionContainerImpl* context,IInnerState* state,InnerEventHandler eventHandler,RefCountPtr eventArgs)
	{
		(state->*eventHandler)(context,this,eventArgs);
	}

};

/**
 * Represents the implementation for the RegionBase class without dispatched event arguments.
 * @tparam RegionImpl The inheriting class.
 * @tparam RegionContainerImpl
 * @tparam StateInterface
 * @tparam EventArgs
 */
template
< class RegionImpl
, class RegionContainerImpl
, class IInnerState
, class EventArgs
>
class RegionBaseImplWithoutEventArgs
: public RegionBase<RegionContainerImpl,IInnerState,EventArgs>
{
public:
    /**
     * The implementation class type.
     */
    typedef RegionImpl Implementation;

    /**
     * The RegionBase class type.
     */
    typedef RegionBase<RegionContainerImpl,IInnerState,EventArgs> RegionBaseClass;

    typedef typename RegionBaseClass::RegionContainerClass RegionContainerClass;

    typedef typename RegionBaseClass::RefCountPtr RefCountPtr;

    typedef typename RegionBaseClass::InnerEventHandler InnerEventHandler;

    RegionBaseImplWithoutEventArgs(RegionContainerClass* argRegionContainer)
    : RegionBaseClass(argRegionContainer)
    {}

    virtual ~RegionBaseImplWithoutEventArgs() {}

    virtual void handleBroadcastedEvent(RegionContainerImpl* context,InnerEventHandler eventHandler)
	{
		(static_cast<Implementation*>(this)->*eventHandler)(context);
	}

	/**
	 * Dispatches an event to a state inside the region. The state event handler will be executed
	 * within the context of the internal region thread.
	 * @param context
	 * @param state
	 * @param eventHandler
	 */
	void dispatchEvent(RegionContainerClass* context,IInnerState* state, InnerEventHandler eventHandler)
	{
		if(state)
		{
			RegionContainerImpl* regionContainerContext = static_cast<RegionContainerImpl*>(context);
			queueDispatchedEvent(sttcl::internal::DispatchedEvent<RegionContainerImpl,IInnerState,void>(regionContainerContext,state,eventHandler,RefCountPtr()));
		}
	}

protected:
	void callDispatchedEventHandler(RegionContainerClass* context,IInnerState* state,InnerEventHandler eventHandler,RefCountPtr eventArgs)
	{
		(state->*eventHandler)(context,this);
	}
};

/**
 * Used to select the region base implementation.
 * @tparam RegionContainerImpl
 * @tparam StateInterface
 * @tparam EventArgs
 */
template
< class RegionImpl
, class RegionContainerImpl
, class IInnerState
, class EventArgs
>
struct RegionBaseImplementationSelector
{
	/**
	 * The region base implementation type.
	 */
	typedef RegionBaseImplWithEventArgs<RegionImpl,RegionContainerImpl,IInnerState,EventArgs> RESULT_TYPE;

};

/**
 * Specializes RegionBaseImplementationSelector for void (i.e. no) event arguments.
 */
template
< class RegionImpl
, class RegionContainerImpl
, class IInnerState
>
struct RegionBaseImplementationSelector<RegionImpl,RegionContainerImpl,IInnerState,void>
{
	/**
	 * The region base implementation type.
	 */
	typedef RegionBaseImplWithoutEventArgs<RegionImpl,RegionContainerImpl,IInnerState,void> RESULT_TYPE;

};
}

/**
 * Represents a region within a matching ConcurrentCompositeState implementation.
 * @tparam RegionImpl The inheriting class.
 * @tparam RegionContainerImpl The sttcl::StateMachine class that contains the matching
 *         ConcurrentCompositeState implementation.
 * @tparam IInnerState The inner state event handler interface for the states contained in
 *                     the implementing region.
 * @tparam EventArgs The type of event arguments passed to the inner state event handler
 *                   methods.
 * @tparam HistoryType Specifies the composite state history behavior (see also
 *                     CompositeStateHistoryType::Values), default is
 *                     CompositeStateHistoryType::None.
 * @tparam StateThreadType The thread implementation class, default is
 *                         \link sttcl::internal::SttclThread\endlink<>.
 * @tparam SemaphoreType The semaphore implementation class, default is
 *                                  \link sttcl::internal::SttclSemaphore\endlink<>.
 * @tparam TimeDurationType The time duration representation implementation class, default
 *                          is \link sttcl::TimeDuration\endlink<>.
 * @tparam MutexType The mutex implementation class, default
 *                              is \link sttcl::internal::SttclMutex\endlink<>.
 * @tparam EventQueueType The event queue implementation class, default
 *                        is \link sttcl::EventQueue\endlink<>
 */
template
< class RegionImpl
, class RegionContainerImpl
, class IInnerState
, class EventArgs = void
, CompositeStateHistoryType::Values HistoryType = CompositeStateHistoryType::None
, class StateThreadType = sttcl::internal::SttclThread<>
, class TimeDurationType = TimeDuration<STTCL_DEFAULT_TIMEDURATIONIMPL>
, class SemaphoreType = sttcl::internal::SttclSemaphore<STTCL_DEFAULT_SEMAPHOREIMPL,TimeDurationType>
, class MutexType = sttcl::internal::SttclMutex<STTCL_DEFAULT_MUTEXIMPL,TimeDurationType>
, class EventQueueType = sttcl::EventQueue<sttcl::internal::DispatchedEvent<RegionContainerImpl,IInnerState,EventArgs>,TimeDurationType,SemaphoreType,MutexType>
>
class Region
: public CompositeState
  	< Region<RegionImpl,RegionContainerImpl,IInnerState,EventArgs,HistoryType,StateThreadType,TimeDurationType,SemaphoreType,MutexType,EventQueueType>
	, RegionContainerImpl
	, IInnerState
	, HistoryType
	, ActiveState
	  < Region<RegionImpl,RegionContainerImpl,IInnerState,EventArgs,HistoryType,StateThreadType,TimeDurationType,SemaphoreType,MutexType,EventQueueType>
	  , RegionContainerImpl
	  , IInnerState
	  , StateThreadType
	  , TimeDurationType
	  , SemaphoreType
	  , MutexType
	  >
	, StateMachine<RegionImpl, IInnerState>
	>
, public internal::RegionBaseImplementationSelector
	< RegionImpl
	, RegionContainerImpl
	, IInnerState
	, EventArgs
	>::RESULT_TYPE
{
public:
	friend class RegionBase<RegionContainerImpl,IInnerState,EventArgs>;

    /**
     * The implementation class type.
     */
    typedef RegionImpl Implementation;

    /**
     * The state machine implementation type.
     */
    typedef RegionContainerImpl Context;

    /**
     * The actual Region class type, just to shorten typing for implementation.
     */
    typedef Region
    			< RegionImpl
    			, RegionContainerImpl
    			, IInnerState
    			, EventArgs
    			, HistoryType
    			, StateThreadType
                , TimeDurationType
                , SemaphoreType
                , MutexType
                , EventQueueType
                > SelfClassType;
    /**
     * The \link sttcl::ActiveState\endlink<> implementation to use as state implementation
     * base of the CompositeState base class.
     */
    typedef ActiveState
    		  < SelfClassType
    		  , RegionContainerImpl
    		  , IInnerState
    		  , StateThreadType
    		  , TimeDurationType
    		  , SemaphoreType
    		  , MutexType
    		  > ActiveStateImpl;

    /**
     * The region composites state base class type.
     */
    typedef CompositeState
    	  	< SelfClassType
    		, RegionContainerImpl
    		, IInnerState
    		, HistoryType
    		, ActiveStateImpl
    		, StateMachine<RegionImpl, IInnerState>
    		> CompositeStateBase;

    /**
     * The selected RegionBase implementation class type.
     */
    typedef typename internal::RegionBaseImplementationSelector<RegionImpl,RegionContainerImpl,IInnerState,EventArgs>::RESULT_TYPE SelectedRegionBase;

    typedef typename SelectedRegionBase::RegionBaseClass RegionBaseClass;

    typedef sttcl::internal::EventArgsInterfaceSelector<RegionContainerImpl,IInnerState,EventArgs> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::RefCountPtr RefCountPtr;

	/**
     * The inner event handler signature.
     */
	typedef typename EventArgsSelectorType::InnerEventHandler InnerEventHandler;

    /**
     * The internal event handler signature.
     */
    typedef void (RegionBaseClass::*InternalEventHandler)(bool);

    /**
     * The (composite) state implementation base class type.
     */
    typedef typename CompositeStateBase::StateImplementationBase StateImplementationBase;

    /**
     * The (composite) state machine base class type.
     */
    typedef typename CompositeStateBase::StateMachineImplementationBase RegionStateMachine;

    /**
     * The state do action type.
     */
    typedef typename CompositeStateBase::StateDoAction StateDoAction;

    /**
     * The composite state base class regarding state history policy.
     */
	typedef typename CompositeStateBase::CompositeStateHistoryBaseClass CompositeStateHistoryBaseClass;

	/**
	 * The inner state class.
	 */
	//typedef StateBase<RegionImpl,InnerEventHandler> InnerStateClass;
	typedef typename CompositeStateBase::InnerStateClass InnerStateClass;

	/**
	 * The outer state interface.
	 */
	typedef typename CompositeStateBase::OuterStateInterface OuterStateInterface;

	/**
	 * The state interface.
	 */
	typedef typename CompositeStateBase::StateInterface StateInterface;

	/**
	 * The StateBase class type.
	 */
	typedef StateBase<RegionImpl,IInnerState> RegionStateBase;

	/**
	 * The StateBase class type.
	 */
	typedef RegionStateBase StateBaseClass;

	/**
	 * The region state thread class type.
	 */
    typedef typename StateImplementationBase::StateThreadImpl RegionThreadImpl;

    /**
     * Constructor for class Region.
     * @param argRegionContainer
     * @param argDoActionFrequency
     */
	Region(RegionContainerImpl* argRegionContainer, TimeDurationType argDoActionFrequency = TimeDurationType::Zero)
	: CompositeStateBase(&SelfClassType::regionDoAction)
	, SelectedRegionBase(argRegionContainer)
	, eventDispatchQueue()
	, checkEventFrequency(argDoActionFrequency)
	{
	}

	/**
	 * Destructor for class Region.
	 */
	virtual ~Region()
	{
	}

	/**
	 * Dispatches an internal event to be executed within the context of the internal region
	 * thread.
	 * @param internalEventHandler
	 * @param recursive
	 */
	void dispatchInternalEvent(InternalEventHandler internalEventHandler, bool recursive)
	{
		eventDispatchQueue.push_back(sttcl::internal::DispatchedEvent<RegionContainerImpl,IInnerState,EventArgs>(internalEventHandler,recursive));
	}

    /**
     * Default implementation for the changeState() method.
     * @param context A pointer to the containing state machine.
     * @param newState The new sibling state the containing state machine should change to.
     */
    void changeStateImpl(RegionContainerImpl* context,IInnerState* newState)
    {
    }

	/**
	 * Changes the region composite state machine to \em newState.
	 * @param newState
	 */
	void changeState(RegionStateBase* newState)
	{
		RegionStateMachine::changeState(newState);
	}

	/**
	 * Called when the region thread is started.
	 */
	void startingRegionThread()
	{

	}

	/**
	 * Called when the region thread is stopped.
	 */
	void endingRegionThread()
	{

	}

	/**
	 * Default entry() method implementation.
	 * @param context
	 */
    void entryImpl(Context* context)
    {
    	CompositeStateBase::entryImpl(context);
    }

	/**
	 * Default exit() method implementation.
	 * @param context
	 */
    void exitImpl(Context* context)
    {
    	CompositeStateBase::exitImpl(context);
    }

    /**
     * Default initialize() method implementation.
     * @param force
     * @return
     */
    bool initializeImpl(bool force)
    {
    	if(!RegionThreadImpl::isSelf(static_cast<StateImplementationBase*>(this)->getStateThread()))
    	{
			// dispatch initialization to region thread
        	dispatchInternalEvent(&RegionBaseClass::internalInitialize,force);
    	}
    	else
    	{
    		internalInitialize(force);
    	}
    	return true;
    }

    /**
     * Default implementation for finalize().
     *
     * @param finalizeSubStateMachines Indicates to finalize any sub state machines.
     */
    inline void finalizeImpl(bool finalizeSubStateMachines)
    {
    	if(!RegionThreadImpl::isSelf(static_cast<StateImplementationBase*>(this)->getStateThread()))
    	{
			// dispatch finalization to region thread
			dispatchInternalEvent(&RegionBaseClass::internalFinalize,finalizeSubStateMachines);
    	}
    	else
    	{
    		internalFinalize(finalizeSubStateMachines);
    	}
    }

    /**
     * Default implementation for the endDoActionRequested() method.
     * @return
     */
    bool endDoActionRequestedImpl()
    {
    	return //static_cast<RegionContainerImplementationBase*>(this)->isFinalized() ||
    		   static_cast<StateImplementationBase*>(this)->endDoActionRequestedImpl();
    }

    /**
     * Default implementation for the exitingDoAction() method.
     */
    void exitingDoActionImpl()
    {
		static_cast<RegionImpl*>(this)->endingRegionThread();
    }

    /**
     * Called when the ActiveState::endDoImpl() method is called.
     */
    void joinDoActionThreadImpl()
    {
		static_cast<StateImplementationBase*>(this)->joinDoActionThreadImpl();
    }

    /**
     * Called by the ActiveState::endDoImpl() method to unblock any blocking methods
     * waiting in the internal region thread.
     */
    void unblockDoActionImpl()
    {
 		static_cast<StateImplementationBase*>(this)->unblockDoActionImpl();
		unblockEventsAvailable();
    }

    /**
     * Default implementation of the ActiveState::endDo() method.
     * @param context
     */
    void endDoImpl(RegionContainerImpl* context)
    {
	   if(!RegionThreadImpl::isSelf(static_cast<StateImplementationBase*>(this)->getStateThread()))
	   {
		   static_cast<StateImplementationBase*>(this)->endDoImpl(context);
	   }
    }

private:
	virtual void queueDispatchedEvent(const sttcl::internal::DispatchedEvent<RegionContainerImpl,IInnerState,EventArgs>& dispatchedEvent)
	{
		eventDispatchQueue.push_back(dispatchedEvent);
	}

	virtual void enterRegion(RegionContainerImpl* context)
	{
		static_cast<StateBase<RegionContainerImpl,IInnerState>*>(this)->entry(context);
	}

	virtual void exitRegion(RegionContainerImpl* context)
	{
		static_cast<StateBase<RegionContainerImpl,IInnerState>*>(this)->exit(context);
	}

	virtual void startDoRegion(RegionContainerImpl* context)
	{
		static_cast<RegionImpl*>(this)->startingRegionThread();
		static_cast<StateBase<RegionContainerImpl,IInnerState>*>(this)->startDo(context);
	}

	virtual void endDoRegion(RegionContainerImpl* context)
	{
		static_cast<StateBase<RegionContainerImpl,IInnerState>*>(this)->endDo(context);
	}

	virtual void finalizeRegion(bool recursive)
	{
		static_cast<RegionImpl*>(this)->finalize(recursive);
	}

	virtual bool initializeRegion(bool recursive)
	{
		static_cast<RegionImpl*>(this)->initialize(recursive);
		return static_cast<RegionImpl*>(this)->isReady();
	}

	virtual bool isRegionInitialized()
	{
		return static_cast<RegionImpl*>(this)->isInitialized();
	}

	virtual bool isRegionFinalized()
	{
		return static_cast<RegionImpl*>(this)->isFinalized();
	}

	virtual bool isRegionThreadRunning() const
	{
		return static_cast<const RegionImpl*>(this)->isDoActionRunning();
	}

	virtual void joinRegionThread()
	{
		static_cast<RegionImpl*>(this)->joinDoActionThreadImpl();
	}

	virtual void internalInitialize(bool recursive)
	{
    	static_cast<RegionStateMachine*>(this)->initializeImpl(recursive);
	}

	virtual void internalFinalize(bool recursive)
	{
    	static_cast<RegionStateMachine*>(this)->finalizeImpl(recursive);
    	typedef sttcl::internal::RegionContainer<RegionContainerImpl,IInnerState,EventArgs> IRegionContainer;
    	IRegionContainer* iregionContainer = static_cast<IRegionContainer*>(RegionBaseClass::regionContainer);
    	iregionContainer->regionCompleted(static_cast<RegionBase<RegionContainerImpl,IInnerState,EventArgs>*>(this));
	}

	void unblockEventsAvailable()
	{
		eventDispatchQueue.unblock();
	}

	bool checkEventsAvailable()
	{
		return eventDispatchQueue.waitForEvents(checkEventFrequency);
	}

	void regionDoAction(typename ActiveStateImpl::Context* context, bool firstCall)
	{
		if(checkEventsAvailable())
		{
			while(!eventDispatchQueue.empty())
			{
				sttcl::internal::DispatchedEvent<RegionContainerImpl,IInnerState,EventArgs> dispatchedEvent = eventDispatchQueue.front();
				eventDispatchQueue.pop_front();
				if(dispatchedEvent.internalHandler)
				{
					(this->*dispatchedEvent.internalHandler)(dispatchedEvent.recursiveInternalEvent);
				}
				else
				{
					callDispatchedEventHandler(dispatchedEvent.context,dispatchedEvent.state,dispatchedEvent.handler,dispatchedEvent.eventArgs);
				}
			}
		}
	}

	EventQueueType eventDispatchQueue;
	TimeDurationType checkEventFrequency;
};

}

#endif /* REGION_H_ */
