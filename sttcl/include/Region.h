/*
 * Region.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef REGION_H_
#define REGION_H_

#include "CompositeState.h"
#include "ActiveState.h"
#include "SttclMutex.h"
#include "SttclSemaphore.h"
#include <deque>

namespace sttcl
{

/**
 * Represents the abstract Region base class.
 * @tparam StateMachineImpl
 * @tparam StateInterface
 * @tparam EventArgs
 */
template
< class StateMachineImpl
, class StateInterface
, class EventArgs = void
>
class RegionBase
{
public:
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
	 * The inner states event handler signature. All methods of the IInnerState interface
	 * must have this signature. The first parameter is a pointer to the containing state
	 * machine. The second parameter is a pointer to additional event arguments as specified
	 * with the EventArgs template parameter.
	 */
    typedef void (StateInterface::*EventHandler)(StateMachineImpl*, const EventArgs*);

    /**
     * Called to handle an event broadcasted from the containing ConcurrentCompositeState instance.
     * @param context A pointer to the containing state machine.
     * @param eventHandler The event handler to call inside the region thread.
     * @param eventArgs The event arguments to pass to the event handler call.
     */
	virtual void handleBroadcastedEvent(StateMachineImpl* context,EventHandler eventHandler, const EventArgs* eventArgs) = 0;
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

};

/**
 * Represents a region within a matching ConcurrentCompositeState implementation.
 * @tparam RegionImpl
 * @tparam StateMachineImpl
 * @tparam IInnerState
 * @tparam EventArgs
 * @tparam HistoryType
 */
template
< class RegionImpl
, class StateMachineImpl
, class IInnerState
, class EventArgs = void
, CompositeStateHistoryType::Values HistoryType = CompositeStateHistoryType::None
>
class Region
: public CompositeState
  	< Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>
	, StateMachineImpl
	, IInnerState
	, HistoryType
	, ActiveState
		< Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>
		, StateMachineImpl
		, typename StateMachineImpl::StateInterface
		>
	, StateMachine<RegionImpl, IInnerState>
	>
, public RegionBase<StateMachineImpl,typename StateMachineImpl::StateInterface,EventArgs>
{
public:
	friend class RegionBase<StateMachineImpl,typename StateMachineImpl::StateInterface,EventArgs>;

    /**
     * The implementation class type.
     */
    typedef RegionImpl Implementation;

    /**
     * The state machine implementation type.
     */
    typedef StateMachineImpl Context;

    /**
     * The region composites state base class type.
     */
    typedef CompositeState
    	  	< Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>
    		, StateMachineImpl
    		, IInnerState
    		, HistoryType
    		, ActiveState
    			< Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>
    			, StateMachineImpl
    			, typename StateMachineImpl::StateInterface
    			>
    		, StateMachine<RegionImpl, IInnerState>
    		> CompositeStateBase;

    /**
     * The RegionBase class type.
     */
    typedef RegionBase<StateMachineImpl,typename StateMachineImpl::StateInterface,EventArgs> RegionBaseClass;

    /**
     * The outer event handler signature.
     */
    typedef typename RegionBaseClass::EventHandler OuterEventHandler;

    /**
     * The inner event handler signature.
     */
    typedef void (IInnerState::*InnerEventHandler)(RegionBaseClass*,const EventArgs*);

    /**
     * The internal event handler signature.
     */
    typedef void (Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>::*InternalEventHandler)(bool);

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
	Region(sttcl::TimeDuration<> argDoActionFrequency = sttcl::TimeDuration<>::Zero)
	: CompositeStateBase(&Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>::regionDoAction)
	, eventsAvailable(0)
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
	 * Dispatches an event to a state inside the region. The state event handler will be executed
	 * within the context of the internal region thread.
	 * @param state
	 * @param eventHandler
	 * @param eventArgs
	 */
	void dispatchEvent(IInnerState* state, InnerEventHandler eventHandler, const EventArgs* eventArgs)
	{
		if(state)
		{
			AutoLocker<SttclMutex<> > lock(eventDispatchMutex);
			eventDispatchQueue.push_back(DispatchedEvent(state,eventHandler,eventArgs));
			unblockEventsAvailable();
		}
	}

	/**
	 * Dispatches an internal event to be executed within the context of the internal region
	 * thread.
	 * @param internalEventHandler
	 * @param recursive
	 */
	void dispatchInternalEvent(InternalEventHandler internalEventHandler, bool recursive)
	{
		AutoLocker<SttclMutex<> > lock(eventDispatchMutex);
		eventDispatchQueue.push_back(DispatchedEvent(internalEventHandler,recursive));
		unblockEventsAvailable();
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
    	// dispatch initialization to region thread
    	dispatchInternalEvent(&Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>::internalInitialize,force);
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
			dispatchInternalEvent(&Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>::internalFinalize,finalizeSubStateMachines);
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
	virtual void handleBroadcastedEvent(StateMachineImpl* context,OuterEventHandler eventHandler, const EventArgs* eventArgs)
	{
		(static_cast<Implementation*>(this)->*eventHandler)(context,eventArgs);
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

	void internalInitialize(bool recursive)
	{
    	static_cast<StateMachineImplementationBase*>(this)->initializeImpl(recursive);
	}

	void internalFinalize(bool recursive)
	{
    	static_cast<StateMachineImplementationBase*>(this)->finalizeImpl(recursive);
	}

	struct DispatchedEvent
	{
		IInnerState* state;
		InnerEventHandler handler;
		const EventArgs* eventArgs;
		InternalEventHandler internalHandler;
		bool recursiveInternalEvent;

		DispatchedEvent(IInnerState* argState, InnerEventHandler argHandler, const EventArgs* argEventArgs)
		: state(argState)
		, handler(argHandler)
		, eventArgs(argEventArgs)
		, internalHandler(0)
		, recursiveInternalEvent(false)
		{
		}

		DispatchedEvent(InternalEventHandler argInternalHandler, bool argRecursiveInternalEvent)
		: state(0)
		, handler(0)
		, eventArgs(0)
		, internalHandler(argInternalHandler)
		, recursiveInternalEvent(argRecursiveInternalEvent)
		{
		}

		DispatchedEvent(const DispatchedEvent& rhs)
		: state(rhs.state)
		, handler(rhs.handler)
		, eventArgs(rhs.eventArgs)
		, internalHandler(rhs.internalHandler)
		, recursiveInternalEvent(rhs.recursiveInternalEvent)
		{
		}
	};

	void unblockEventsAvailable()
	{
		eventsAvailable.post();
	}

	bool checkEventsAvailable()
	{
		return eventsAvailable.try_wait(checkEventFrequency);
	}

	void regionDoAction(Context* context, bool firstCall)
	{
		if(checkEventsAvailable())
		{
			AutoLocker<SttclMutex<> > lock(eventDispatchMutex);
			while(!eventDispatchQueue.empty())
			{
				DispatchedEvent dispatchedEvent = eventDispatchQueue.front();
				eventDispatchQueue.pop_front();
				if(dispatchedEvent.internalHandler)
				{
					(this->*dispatchedEvent.internalHandler)(dispatchedEvent.recursiveInternalEvent);
				}
				else
				{
					(dispatchedEvent.state->*dispatchedEvent.handler)(this,dispatchedEvent.eventArgs);
				}
			}
		}
	}

	SttclMutex<> eventDispatchMutex;
	SttclSemaphore<> eventsAvailable;
	std::deque<DispatchedEvent> eventDispatchQueue;
	sttcl::TimeDuration<> checkEventFrequency;
};

}

#endif /* REGION_H_ */
