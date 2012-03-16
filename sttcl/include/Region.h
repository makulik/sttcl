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
#include "EventArgsPtr.h"
#include "SttclMutex.h"
#include "SttclSemaphore.h"
#if !defined(STTCL_USE_STL)
#else
#include <deque>
#endif

namespace sttcl
{

template
< class StateMachineImpl
, class StateInterface
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
< class StateMachineImpl
, class StateInterface
, class IInnerState
, class EventArgsType
>
struct EventArgsInterfaceSelector
{
	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef sttcl::EventArgsPtr<EventArgsType> EventArgsPtr;

	/**
	 * The region event handler signature. All methods of the \em StateInterface interface
	 * must have this signature. The first parameter is a pointer to the containing state
	 * machine. The second parameter is a pointer to additional event arguments as specified
	 * with the EventArgs template parameter.
	 */
    typedef void (StateInterface::*OuterEventHandler)(StateMachineImpl*,EventArgsPtr);

    /**
	 * The inner states event handler signature. All methods of the \em IInnerState interface
	 * must have this signature. The first parameter is a pointer to the containing state
	 * machine. The second parameter is a pointer to the region base class that contains the
	 * inner state. The third parameter is a pointer to additional event arguments as specified
	 * with the EventArgs template parameter.
	 */
    typedef void (IInnerState::*InnerEventHandler)(StateMachineImpl*,RegionBase<StateMachineImpl,StateInterface,IInnerState,EventArgsType>*,EventArgsPtr);
};

/**
 * Specializes EventArgsInterfaceSelector for void (i.e. no) event arguments.
 */
template
< class StateMachineImpl
, class StateInterface
, class IInnerState
>
struct EventArgsInterfaceSelector<StateMachineImpl,StateInterface,IInnerState,void>
{
	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef sttcl::EventArgsPtr<void> EventArgsPtr;

	/**
	 * The region event handler signature. All methods of the \em StateInterface interface
	 * must have this signature. The first parameter is a pointer to the containing state
	 * machine. The second parameter is a pointer to additional event arguments as specified
	 * with the EventArgs template parameter.
	 */
    typedef void (StateInterface::*OuterEventHandler)(StateMachineImpl*);

    /**
	 * The inner states event handler signature. All methods of the IInnerState interface
	 * must have this signature. The first parameter is a pointer to the containing state
	 * machine. The second parameter is a pointer to additional event arguments as specified
	 * with the EventArgs template parameter.
	 */
    typedef void (IInnerState::*InnerEventHandler)(StateMachineImpl*,RegionBase<StateMachineImpl,StateInterface,IInnerState,void>*);
};

template
< class StateMachineImpl
, class StateInterface
, class IInnerState
, class EventArgs
> class IRegionEventDispatchWithArgs
{
public:
	typedef EventArgsInterfaceSelector<StateMachineImpl,StateInterface,IInnerState,EventArgs> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::EventArgsPtr EventArgsPtr;

	/**
     * The outer event handler signature.
     */
	typedef typename EventArgsSelectorType::OuterEventHandler OuterEventHandler;

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
	virtual void handleBroadcastedEvent(StateMachineImpl* context,OuterEventHandler eventHandler, EventArgsPtr eventArgs) = 0;

	virtual ~IRegionEventDispatchWithArgs() {}
};

template
< class StateMachineImpl
, class StateInterface
, class IInnerState
, class EventArgs
> class IRegionEventDispatchWithoutArgs
{
public:
	typedef EventArgsInterfaceSelector<StateMachineImpl,StateInterface,IInnerState,EventArgs> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::EventArgsPtr EventArgsPtr;

	/**
     * The outer event handler signature.
     */
	typedef typename EventArgsSelectorType::OuterEventHandler OuterEventHandler;

	/**
     * The inner event handler signature.
     */
	typedef typename EventArgsSelectorType::InnerEventHandler InnerEventHandler;

	/**
     * Called to handle an event broadcasted from the containing ConcurrentCompositeState instance.
     * @param context A pointer to the containing state machine.
     * @param eventHandler The event handler to call inside the region thread.
     */
	virtual void handleBroadcastedEvent(StateMachineImpl* context,OuterEventHandler eventHandler) = 0;

	virtual ~IRegionEventDispatchWithoutArgs() {}
};

/**
 * Used to select the region event dispatch interface.
 * @tparam StateMachineImpl
 * @tparam StateInterface
 * @tparam EventArgs
 */
template
< class StateMachineImpl
, class StateInterface
, class IInnerState
, class EventArgs
>
struct RegionEventDispatchInterfaceSelector
{
	/**
	 * The region base event dispatch interface type.
	 */
	typedef IRegionEventDispatchWithArgs<StateMachineImpl,StateInterface,IInnerState,EventArgs> RESULT_TYPE;

};

/**
 * Specializes RegionEventDispatchInterfaceSelector for void (i.e. no) event arguments.
 */
template
< class StateMachineImpl
, class StateInterface
, class IInnerState
>
struct RegionEventDispatchInterfaceSelector<StateMachineImpl,StateInterface,IInnerState,void>
{
	/**
	 * The region base event dispatch interface type.
	 */
	typedef IRegionEventDispatchWithoutArgs<StateMachineImpl,StateInterface,IInnerState,void> RESULT_TYPE;

};

template
< class StateMachineImpl
, class IInnerState
, class EventArgs
>
struct DispatchedEvent;
}

/**
 * Represents the abstract Region base class.
 * @tparam StateMachineImpl
 * @tparam StateInterface
 * @tparam EventArgs
 */
template
< class StateMachineImpl
, class StateInterface
, class IInnerState
, class EventArgs = void
>
class RegionBase
: public sttcl::internal::RegionEventDispatchInterfaceSelector<StateMachineImpl,StateInterface,IInnerState,EventArgs>::RESULT_TYPE
{
public:
	typedef typename sttcl::internal::RegionEventDispatchInterfaceSelector<StateMachineImpl,StateInterface,IInnerState,EventArgs>::RESULT_TYPE RegionEventDispatchInterface;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename RegionEventDispatchInterface::EventArgsPtr EventArgsPtr;

    typedef typename RegionEventDispatchInterface::OuterEventHandler OuterEventHandler;

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
	RegionBase()
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
	virtual void enterRegion(StateMachineImpl* context) = 0;
	/**
	 * Called when the region is left.
     * @param context A pointer to the containing state machine.
	 */
	virtual void exitRegion(StateMachineImpl* context) = 0;
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
	virtual void startDoRegion(StateMachineImpl* context) = 0;
	/**
	 * Called to stop the region thread.
     * @param context A pointer to the containing state machine.
	 */
	virtual void endDoRegion(StateMachineImpl* context) = 0;
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

	virtual void queueDispatchedEvent(const sttcl::internal::DispatchedEvent<StateMachineImpl,IInnerState,EventArgs>& dispatchedEvent) = 0;

};

namespace internal
{

/**
 * Container struct to dispatch events to the inner region thread.
 */
template
< class StateMachineImpl
, class IInnerState
, class EventArgs
>
struct DispatchedEvent
{
    /**
     * The RegionBase class type.
     */
    typedef RegionBase<StateMachineImpl,typename StateMachineImpl::StateInterface,IInnerState,EventArgs> RegionBaseClass;

	typedef EventArgsInterfaceSelector<StateMachineImpl,typename StateMachineImpl::StateInterface,IInnerState,EventArgs> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::EventArgsPtr EventArgsPtr;

	/**
     * The outer event handler signature.
     */
	typedef typename EventArgsSelectorType::OuterEventHandler OuterEventHandler;

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
    StateMachineImpl* context;
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
	mutable EventArgsPtr eventArgs;
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
	DispatchedEvent(StateMachineImpl* argContext, IInnerState* argState, InnerEventHandler argHandler, EventArgsPtr argEventArgs)
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
 * @tparam StateMachineImpl
 * @tparam StateInterface
 * @tparam EventArgs
 */
template
< class RegionImpl
, class StateMachineImpl
, class StateInterface
, class IInnerState
, class EventArgs
>
class RegionBaseImplWithEventArgs
: public RegionBase<StateMachineImpl,StateInterface,IInnerState,EventArgs>
{
public:
    /**
     * The implementation class type.
     */
    typedef RegionImpl Implementation;

    /**
     * The RegionBase class type.
     */
    typedef RegionBase<StateMachineImpl,typename StateMachineImpl::StateInterface,IInnerState,EventArgs> RegionBaseClass;

    typedef typename RegionBaseClass::EventArgsPtr EventArgsPtr;

    typedef typename RegionBaseClass::InnerEventHandler InnerEventHandler;

    typedef typename RegionBaseClass::OuterEventHandler OuterEventHandler;

    RegionBaseImplWithEventArgs()
    : RegionBaseClass()
    {}

    virtual ~RegionBaseImplWithEventArgs() {}

    virtual void handleBroadcastedEvent(StateMachineImpl* context,OuterEventHandler eventHandler, EventArgsPtr eventArgs)
	{
		(static_cast<Implementation*>(this)->*eventHandler)(context,eventArgs);
	}

	/**
	 * Dispatches an event to a state inside the region. The state event handler will be executed
	 * within the context of the internal region thread.
	 * @param context
	 * @param state
	 * @param eventHandler
	 * @param eventArgs
	 */
	void dispatchEvent(StateMachineImpl* context,IInnerState* state, InnerEventHandler eventHandler, EventArgsPtr eventArgs)
	{
		if(state)
		{
			queueDispatchedEvent(sttcl::internal::DispatchedEvent<StateMachineImpl,IInnerState,EventArgs>(context,state,eventHandler,eventArgs));
		}
	}

protected:
	void callDispatchedEventHandler(StateMachineImpl* context,IInnerState* state,InnerEventHandler eventHandler,EventArgsPtr eventArgs)
	{
		(state->*eventHandler)(context,this,eventArgs);
	}

};

/**
 * Represents the implementation for the RegionBase class without dispatched event arguments.
 * @tparam RegionImpl The inheriting class.
 * @tparam StateMachineImpl
 * @tparam StateInterface
 * @tparam EventArgs
 */
template
< class RegionImpl
, class StateMachineImpl
, class StateInterface
, class IInnerState
, class EventArgs
>
class RegionBaseImplWithoutEventArgs
: public RegionBase<StateMachineImpl,StateInterface,IInnerState,EventArgs>
{
public:
    /**
     * The implementation class type.
     */
    typedef RegionImpl Implementation;

    /**
     * The RegionBase class type.
     */
    typedef RegionBase<StateMachineImpl,typename StateMachineImpl::StateInterface,IInnerState,EventArgs> RegionBaseClass;

    typedef typename RegionBaseClass::EventArgsPtr EventArgsPtr;

    typedef typename RegionBaseClass::InnerEventHandler InnerEventHandler;

    typedef typename RegionBaseClass::OuterEventHandler OuterEventHandler;

    RegionBaseImplWithoutEventArgs()
    : RegionBaseClass()
    {}

    virtual ~RegionBaseImplWithoutEventArgs() {}

    virtual void handleBroadcastedEvent(StateMachineImpl* context,OuterEventHandler eventHandler)
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
	void dispatchEvent(StateMachineImpl* context,IInnerState* state, InnerEventHandler eventHandler)
	{
		if(state)
		{
			queueDispatchedEvent(sttcl::internal::DispatchedEvent<StateMachineImpl,IInnerState,void>(context,state,eventHandler,EventArgsPtr()));
		}
	}

protected:
	void callDispatchedEventHandler(StateMachineImpl* context,IInnerState* state,InnerEventHandler eventHandler,EventArgsPtr eventArgs)
	{
		(state->*eventHandler)(context,this);
	}
};

/**
 * Used to select the region base implementation.
 * @tparam StateMachineImpl
 * @tparam StateInterface
 * @tparam EventArgs
 */
template
< class RegionImpl
, class StateMachineImpl
, class StateInterface
, class IInnerState
, class EventArgs
>
struct RegionBaseImplementationSelector
{
	/**
	 * The region base implementation type.
	 */
	typedef RegionBaseImplWithEventArgs<RegionImpl,StateMachineImpl,StateInterface,IInnerState,EventArgs> RESULT_TYPE;

};

/**
 * Specializes RegionBaseImplementationSelector for void (i.e. no) event arguments.
 */
template
< class RegionImpl
, class StateMachineImpl
, class StateInterface
, class IInnerState
>
struct RegionBaseImplementationSelector<RegionImpl,StateMachineImpl,StateInterface,IInnerState,void>
{
	/**
	 * The region base implementation type.
	 */
	typedef RegionBaseImplWithoutEventArgs<RegionImpl,StateMachineImpl,StateInterface,IInnerState,void> RESULT_TYPE;

};
}

#if !defined(STTCL_USE_STL)
#else
#if !defined(STTCL_DEFAULT_DEQUEIMPL)
#define STTCL_DEFAULT_DEQUEIMPL(__T__) std::deque<__T__>
#endif
#endif

#if !defined(STTCL_DEFAULT_DEQUEIMPL)
#error "You need to define a default double ended queue implementation for sttcl"
#endif

namespace internal
{
/**
 * Represents a queue used to dispatch events to a waiting thread.
 */
template
< class T
, class TimeDurationType = TimeDuration<STTCL_DEFAULT_TIMEDURATIONIMPL>
, class SemaphoreType = sttcl::internal::SttclSemaphore<STTCL_DEFAULT_SEMAPHOREIMPL,TimeDurationType>
, class MutexType = sttcl::internal::SttclMutex<STTCL_DEFAULT_MUTEXIMPL,TimeDurationType>
, class InnerQueueType = STTCL_DEFAULT_DEQUEIMPL(T)
// , class InnerQueueType = std::deque<T>
>
class SttclEventQueue
{
public:
	/**
	 * Constructor for class SttclEventQueue.
	 */
	SttclEventQueue()
	: eventQueue()
	{
	}
	/**
	 * Destructor for class SttclEventQueue.
	 */
	~SttclEventQueue()
	{
	}

	/**
	 * Puts an event to the end of the queue and signals that events are available.
	 * @param event
	 */
	void push_back(const T& event)
	{
		{ sttcl::internal::AutoLocker<MutexType> lock(eventQueueMutex);
			eventQueue.push_back(event);
		}
		eventsAvailable.post();
	}

	/**
	 * Gets the event from the front of the queue.
	 * @return
	 */
	T& front()
	{
		sttcl::internal::AutoLocker<MutexType> lock(eventQueueMutex);
		return eventQueue.front();
	}

	/**
	 * Removes the item at front of the queue.
	 */
	void pop_front()
	{
		sttcl::internal::AutoLocker<MutexType> lock(eventQueueMutex);
		eventQueue.pop_front();
	}

	/**
	 * Blocks the calling thread until events are available in the queue.
	 * @return \c true if events are available, \c false if an error occurred.
	 */
	bool waitForEvents()
	{
		return eventsAvailable.wait() && !empty();
	}

	/**
	 * Blocks the calling thread until events are available in the queue.
	 * @return \c true if events are available, \c false if no events were available within the
	 *         specified timeout.
	 */
	bool waitForEvents(TimeDurationType timeout)
	{
		return eventsAvailable.try_wait(timeout) && !empty();
	}

	/**
	 * Indicates that the event queue is empty.
	 * @return \c true if the queue is empty, \c false otherwise.
	 */
	bool empty()
	{
		sttcl::internal::AutoLocker<MutexType> lock(eventQueueMutex);
		return eventQueue.empty();
	}

	/**
	 * Unblocks waiting threads.
	 */
	void unblock()
	{
		eventsAvailable.post();
	}
private:
	InnerQueueType eventQueue;
	MutexType eventQueueMutex;
	SemaphoreType eventsAvailable;
};


}

/**
 * Represents a region within a matching ConcurrentCompositeState implementation.
 * @tparam RegionImpl The inheriting class.
 * @tparam StateMachineImpl The sttcl::StateMachine class that contains the matching
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
 *                        is \link sttcl::internal::SttclEventQueue\endlink<>
 */
template
< class RegionImpl
, class StateMachineImpl
, class IInnerState
, class EventArgs = void
, CompositeStateHistoryType::Values HistoryType = CompositeStateHistoryType::None
, class StateThreadType = sttcl::internal::SttclThread<>
, class TimeDurationType = TimeDuration<STTCL_DEFAULT_TIMEDURATIONIMPL>
, class SemaphoreType = sttcl::internal::SttclSemaphore<STTCL_DEFAULT_SEMAPHOREIMPL,TimeDurationType>
, class MutexType = sttcl::internal::SttclMutex<STTCL_DEFAULT_MUTEXIMPL,TimeDurationType>
, class EventQueueType = sttcl::internal::SttclEventQueue<sttcl::internal::DispatchedEvent<StateMachineImpl,IInnerState,EventArgs>,TimeDurationType,SemaphoreType,MutexType>
>
class Region
: public CompositeState
  	< Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType,StateThreadType,TimeDurationType,SemaphoreType,MutexType,EventQueueType>
	, StateMachineImpl
	, IInnerState
	, HistoryType
	, ActiveState
	  < Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType,StateThreadType,TimeDurationType,SemaphoreType,MutexType,EventQueueType>
	  , StateMachineImpl
	  , typename StateMachineImpl::StateInterface
	  , StateThreadType
	  , TimeDurationType
	  , SemaphoreType
	  , MutexType
	  >
	, StateMachine<RegionImpl, IInnerState>
	>
, public internal::RegionBaseImplementationSelector
	< RegionImpl
	, StateMachineImpl
	, typename StateMachineImpl::StateInterface
	, IInnerState
	, EventArgs
	>::RESULT_TYPE
{
public:
	friend class RegionBase<StateMachineImpl,typename StateMachineImpl::StateInterface,IInnerState,EventArgs>;

    /**
     * The implementation class type.
     */
    typedef RegionImpl Implementation;

    /**
     * The state machine implementation type.
     */
    typedef StateMachineImpl Context;

    /**
     * The actual Region class type, just to shorten typing for implementation.
     */
    typedef Region
    			< RegionImpl
    			, StateMachineImpl
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
    		  , StateMachineImpl
    		  , typename StateMachineImpl::StateInterface
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
    		, StateMachineImpl
    		, IInnerState
    		, HistoryType
    		, ActiveStateImpl
    		, StateMachine<RegionImpl, IInnerState>
    		> CompositeStateBase;

    /**
     * The selected RegionBase implementation class type.
     */
    typedef typename internal::RegionBaseImplementationSelector<RegionImpl,StateMachineImpl,typename StateMachineImpl::StateInterface,IInnerState,EventArgs>::RESULT_TYPE SelectedRegionBase;

    typedef typename SelectedRegionBase::RegionBaseClass RegionBaseClass;

    typedef sttcl::internal::EventArgsInterfaceSelector<StateMachineImpl,typename StateMachineImpl::StateInterface,IInnerState,EventArgs> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::EventArgsPtr EventArgsPtr;

	/**
     * The outer event handler signature.
     */
	typedef typename EventArgsSelectorType::OuterEventHandler OuterEventHandler;

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
    typedef typename CompositeStateBase::StateMachineImplementationBase StateMachineImplementationBase;

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
     * @param argDoActionFrequency
     */
	Region(TimeDurationType argDoActionFrequency = TimeDurationType::Zero)
	: CompositeStateBase(&SelfClassType::regionDoAction)
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
		eventDispatchQueue.push_back(sttcl::internal::DispatchedEvent<StateMachineImpl,IInnerState,EventArgs>(internalEventHandler,recursive));
	}

	/**
	 * Changes the region composite state machine to \em newState.
	 * @param newState
	 */
	void changeState(RegionStateBase* newState)
	{
		StateMachineImplementationBase::changeState(newState);
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
    	return //static_cast<StateMachineImplementationBase*>(this)->isFinalized() ||
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
    void endDoImpl(StateMachineImpl* context)
    {
	   if(!RegionThreadImpl::isSelf(static_cast<StateImplementationBase*>(this)->getStateThread()))
	   {
		   static_cast<StateImplementationBase*>(this)->endDoImpl(context);
	   }
    }

private:
	virtual void queueDispatchedEvent(const sttcl::internal::DispatchedEvent<StateMachineImpl,IInnerState,EventArgs>& dispatchedEvent)
	{
		eventDispatchQueue.push_back(dispatchedEvent);
	}

	virtual void enterRegion(StateMachineImpl* context)
	{
		static_cast<StateBase<StateMachineImpl,OuterStateInterface>*>(this)->entry(context);
	}

	virtual void exitRegion(StateMachineImpl* context)
	{
		static_cast<StateBase<StateMachineImpl,OuterStateInterface>*>(this)->exit(context);
	}

	virtual void startDoRegion(StateMachineImpl* context)
	{
		static_cast<RegionImpl*>(this)->startingRegionThread();
		static_cast<StateBase<StateMachineImpl,OuterStateInterface>*>(this)->startDo(context);
	}

	virtual void endDoRegion(StateMachineImpl* context)
	{
		static_cast<StateBase<StateMachineImpl,OuterStateInterface>*>(this)->endDo(context);
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
    	static_cast<StateMachineImplementationBase*>(this)->initializeImpl(recursive);
	}

	virtual void internalFinalize(bool recursive)
	{
    	static_cast<StateMachineImplementationBase*>(this)->finalizeImpl(recursive);
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
				sttcl::internal::DispatchedEvent<StateMachineImpl,IInnerState,EventArgs> dispatchedEvent = eventDispatchQueue.front();
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
